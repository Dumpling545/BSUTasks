#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int m = 12;
const int n = 11;
const int DEF_WIDTH = 32;
const float epsilon = 0.0001;
const int k_max = 1000;
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
/** �������� �� ���������� ��������� ��������
    (������������ �������� ��������� ����������� ���� ��������
     ������ ���� ������ epsilon)
*/
bool isPrecisionReached(std::vector<float> x,
                        std::vector<float> y){
    bool isReached = true;
    for(int i = 0; i < n && isReached; i++){
        isReached = (abs(x[i] - y[i]) < epsilon);
    }
    return isReached;
}

/// �������� �������
std::vector<std::vector<float>> createMatrix(){
    srand(time(NULL));
    std::vector<float> nullvector(n, 0);
    std::vector<std::vector<float>> matrix(n, nullvector);
    float sum;
    for(int i = 0; i < n; i++){
        sum = 0;
        for(int j = 0; j < n; j++){
            matrix[i][j] = -rand()%5;
            sum += matrix[i][j];
        }
        matrix[i][i] -= sum;
    }
    matrix[0][0] += 1;
    return matrix;
}
/// �������� ������� ��������� �������� �� ������� (� ������� x �������)
std::vector<float> createVector(std::vector<std::vector<float>> matrix){
    std::vector<float> v(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            v[i]+= matrix[i][j]*(m + j);
        }
    }
    return v;
}
/// ��������� ���������� ����������� �������
struct IterativeResult{
    ///������������ ������� ����������� �������
    std::vector<float> result;
    /** ����� ��������, �� ������� ���� ���������� �������� ��������.
        -1, ���� ��������� ������������ ���������� ��������*/
    int k;
};
/// ������� ���� ������� �����
IterativeResult jakobiMethod(const std::vector<std::vector<float>> &matrix,
                                const std::vector<float> &f){
    /**����� ��������� �������� x (�� ��������),
       � ������ ������ ��������� ������*/
    std::vector<float> result(n, 0);
    /**�������������� ������ ������� ���������� ��������,
       ������������� ��������� ���, ����� �������� � �������� result
       ���� ������ �������� �������� (����� ���� �� ���������� �� ����)*/
    std::vector<float> previous(n, epsilon*2);
    int iteration;
    for(iteration = 1;
        iteration <= k_max && !isPrecisionReached(result, previous);
        iteration++){
            /** ��������� ��������� result ��� �������� iteration,
                � previous ���������� ��������� �������� (iteration - 1)
            */
            previous = result;
            for(int i = 0; i < n; i++){
                result[i] = f[i];
                for(int j = 0; j < i; j++){
                    result[i] -=matrix[i][j]*previous[j];
                }
                for(int j = i + 1; j < n; j++){
                    result[i] -=matrix[i][j]*previous[j];
                }
                result[i] /= matrix[i][i];
            }
    }
    IterativeResult ir;
    ir.result = result;
    /** ���� �������� ����������, ���������� ����� ��������
        ���� �������� �� ����������, ���������� -1 */
    ir.k = (isPrecisionReached(result, previous)) ? iteration : -1;
    return ir;
}
///������� ���� ������� ����������
IterativeResult sorMethod(const std::vector<std::vector<float>> &matrix,
                                const std::vector<float> &f, float omega){
    /**����� ��������� �������� x (�� ��������),
       � ������ ������ ��������� ������*/
    std::vector<float> result(n, 0);
    /**�������������� ������ ������� ���������� ��������,
       ������������� ��������� ���, ����� �������� � �������� result
       ���� ������ �������� �������� (����� ���� �� ���������� �� ����)*/
    std::vector<float> previous(n, epsilon*2);
    int iteration;
    for(iteration = 1;
        iteration <= k_max && !isPrecisionReached(result, previous);
        iteration++){
            /** ��������� ��������� result ��� �������� iteration,
                � previous ���������� ��������� �������� (iteration - 1)
            */
            previous = result;
            for(int i = 0; i < n; i++){
                result[i] = f[i];
                for(int j = 0; j < i; j++){
                    result[i] -=matrix[i][j]*result[j];
                }
                for(int j = i + 1; j < n; j++){
                    result[i] -=matrix[i][j]*result[j];
                }
                result[i] *= omega / matrix[i][i];
                result[i] += (1 - omega) * previous[i];
            }
    }
    IterativeResult ir;
    ir.result = result;
    /** ���� �������� ����������, ���������� ����� ��������
        ���� �������� �� ����������, ���������� -1 */
    ir.k = (isPrecisionReached(result, previous)) ? iteration : -1;
    return ir;
}
int main()
{
    ///������� ������� �������
    std::vector<std::vector<float>> matrix = createMatrix();
    /**������ ������ f ��������� ������ �� �������
        � ������� ������� x =(m,...,m+n-1)*/
    std::vector<float> f = createVector(matrix);
    ///������� ������� � ������
    cout << "Input:\n\n Matrix:\n";
    printMatrix(matrix, 4);
    cout << "\n\n Vector:\n";
    printVector(f, 4);
    ///������ ���� ������� �����
    cout << "\n\nJAKOBI METHOD: \n";
    IterativeResult jakobi = jakobiMethod(matrix, f);
    ///������� ��������� � ��������, �� ������� ���������� ����������� ��������
    cout << "\n\nResult:\n";
    cout << "\n       Iteration: ";
    if(jakobi.k == -1){
        cout << "precision isn't reached on k_max iterations\n";
    } else {
        cout << jakobi.k<<"\n";
    }
    cout << "\n       Vector: \n";
    printVector(jakobi.result, 12);
    ///������ ���� ������� ���������� ��� ��������� �������� omega
    cout << "\nSOR METHOD: \n";
    for(float omega = 0.5; omega <= 1.5; omega+=0.5){
        cout << "\n\nWITH OMEGA="<<omega<<" \n\n";
        IterativeResult sor = sorMethod(matrix, f, omega);
        /** ������� ��������� � ��������, �� ������� ����������
        ����������� ��������*/
        cout << "\n\nResult:\n";
        cout << "\n       Iteration: ";
        if(sor.k == -1){
            cout << "precision isn't reached on k_max iterations\n";
        } else {
            cout << sor.k<<"\n";
        }
        cout << "\n       Vector: \n";
        printVector(sor.result, 12);
    }
    return 0;
}
