#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

float k = 0;/// int k = 1 ��� ������ 1b
int m = 12;
int n = 10;
const int DEF_WIDTH = 32;
/// ����� ������� � �������
void printMatrix(std::vector<std::vector<float>> matrix, int a = DEF_WIDTH){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << std::setw(a) << matrix[i][j];
        }
        cout <<'\n';
    }
}
/// ����� ������� � �������
void printVector(std::vector<float> v, int a = DEF_WIDTH){
    for(int i = 0; i < n; i++){
        cout << std::setw(a) << v[i];
        cout << '\n';
    }
}
/// ��������� �������
std::vector<std::vector<float>> createMatrix(){
    srand (time(NULL));
    float temp_sum = 0;
    vector<std::vector<float>> matrix(n);
    for(int i = n - 1; i >= 0; i--){
        matrix[i].resize(n);
        temp_sum = 0;
        for(int j = 0; j <= i; j++){
            matrix[i][j] = -rand()%5;
            temp_sum += matrix[i][j];
        }
        for(int j = i+1; j < n; j++){
            matrix[i][j] = matrix[j][i];
            temp_sum += matrix[i][j];
        }
        matrix[i][i] -= temp_sum;
    }
    matrix[0][0] += pow(10.0 , -k);
    return matrix;
}
/// �������� ������� ��������� �������� �� ������� (� ������� x �������)
std::vector<float> createVector(std::vector<std::vector<float>> matrix){
    std::vector<float> v(n, 0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            v[i]+= matrix[i][j]*(m + j);
        }
    }
    return v;
}
/// ����� ���������� �������������� ������� A � ������������ L*D*t(L)
void ldltDecomposition(std::vector<std::vector<float>>& matrix){
    std::vector<float> t(n);
    ///��� �� ������� ����������� ������� (����� ���������)
    for(int s = 0; s < n - 1; s++){
        ///��� �� ���� �������, ��������� �� s-� �������
        for(int i = s + 1; i < n; i++){
            ///�������� ��������� �������� �������� ��-�� (i,s)
            t[i] = matrix[i][s];
            ///� ������� ��� ������� ��-��� ��������� L(i,s) -- �������� ������� L
            matrix[i][s] /= matrix[s][s];
            /**�����, �� i-� ������, ������� �� �������, ���������� �� ���������� L(i,s),
                �������� s-� ������, ���������� �� L(i,s)*/

            /**�.�. ������� �����������, ��  ������� ���� �� ������������� �������� (i,i);
                �� ��� �� ������� ������ ��������� (i,j) - (s,j)*L(i,s) �� ����������
                (i,j) - (j,s)*L(i,s) {�������� (j,s) �������� � t[j]}*/
            for(int j = s + 1; j <= i; j++){
                matrix[i][j] -= t[j] * matrix[i][s];
            }
        }
    }
}
/** ����� ������� ��������� ���� L*X = B

    ����� ������ ����� ������� ���������� ��������� �
    ���������������� ��������
*/
std::vector<float> compute_LX_equals_B(std::vector<std::vector<float>> matrix,
                           std::vector<float> v){
    std::vector<float> result(n);
    /**��������� �� ������ ���� ���� �� ��������� ������� �������,
        �������� �� ���� �������� �������� ����� ������ ������ (����� ����).

        ��� L {����������������} �������� �������� ��������� ������ ������� � ������
        ���������� � ��������� �� ��������� ������� ������ ����, ��������� ��� ����������
        ��������� ���������� ��������, ������� ����� �� ������������
    */
    for(int i = 0; i  < n; i++){
        result[i] = v[i];
        for(int j = 0; j < i; j++){
            result[i] -= matrix[i][j] * result[j];
        }
    }
    return result;
}

/** ����� ������� ��������� ���� t(L)*X = B

    ����� ������ ����� ������� ���������� ��������� �
    ����������������� �������� ���������������� �������
*/
std::vector<float> compute_tLX_equals_F(std::vector<std::vector<float>> matrix,
                           std::vector<float> v){
    std::vector<float> result(n);
    /**��������� �� ������ ���� ���� �� ��������� ������� �������,
        �������� - �������� ��� ������ ������ (� ��� ���� ��������, ��� ��
        ���� ����������������� ��������)
    */
    for(int i = n - 1; i  >= 0; i--){
        result[i] = v[i];
        for(int j = i + 1; j < n; j++){
            result[i] -= matrix[j][i] * result[j];
        }
    }
    return result;
}

/**����� ������� ��������� ���� D*Y=C

    ����� ������ ����� ������� ���������� ��������� �
    ������������ ��������*/
std::vector<float> compute_DX_equals_C(std::vector<std::vector<float>> matrix,
                                       std::vector<float> v){
    std::vector<float> result(n);
    for(int i = 0; i < n; i++){
        result[i] = v[i] / matrix[i][i];
    }
    return result;
}
///���������� ������������� ������ ��� ������ ��������-�����
float relativeError(std::vector<float> result){
    float max_delta = abs(result[0] - m);
    float temp;
    for(int i = 1; i < n; i++){
        temp = abs(result[i] - m - i);
        if(temp > max_delta) max_delta = temp;
    }
    return max_delta / (m + n - 1);
}
int main()
{
    ///������� ������ �� ���� ������: ��� ������ 1.a � 1.b �������������
    std::vector<std::vector<float>> matrix_array[2];
    matrix_array[0] = createMatrix();
    matrix_array[1] = matrix_array[0];
    matrix_array[1][0][0]-=pow(10.0 , -k);
    k = 1;
    matrix_array[1][0][0]+=pow(10.0 , -k);
    for(int p = 0; p < 2; p++){
        cout << "\n\n...................................................................................................\n";
        cout << "WITH K="<<p<<":\n\n";
        ///�������� � ����� ������� ������
        cout << "Input:\n\n Matrix:\n";
        printMatrix(matrix_array[p]);
        cout << "\n\n Vector:\n";
        std::vector<float> v = createVector(matrix_array[p]);
        printVector(v);
        ///���������� LDt(L)
        ldltDecomposition(matrix_array[p]);
        cout << "\n\nLDt(L) decomposition:\n";
        printMatrix(matrix_array[p], 30);
        ///������� ���� c �������������� ����������
        /// ��� 1: ������ ���� LY=b
        std::vector<float> y = compute_LX_equals_B(matrix_array[p], v);
        /// ��� 2: ������ ���� DZ=Y
        std::vector<float> z = compute_DX_equals_C(matrix_array[p], y);
        /// ��� 3: ������ ���� t(L)X=Z
        std::vector<float> result = compute_tLX_equals_F(matrix_array[p], z);
        ///����� ����������
        cout << "\n\nResult:\n";
        printVector(result);
        ///����� ������
        cout << "\n\nRelative Error: "<<setprecision(DEF_WIDTH) << relativeError(result);
    }
    return 0;
}
