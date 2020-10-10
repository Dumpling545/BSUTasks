#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
/// ����� �����
int n = 5;
/** ������ ������� ��� ������ ������:
    ����� ������ ���������� ������������ ���
    �����������, ������� ���� ������� � ��������������
    ������� 12 (m_i, A_i, B_i)
*/
int s = 3*n - 2;

/** �������� ������� ��� ������ ������, ������ n �������� �������������
    ���������� m_0, m_1, ... , m_(n-1),
    ����� n-1 �������� ��� ���������� A_0, A_1, ..., A_(n-2)
    � n-1 �������� ��� ���������� B_0, B_1, ... B_(n-2)
    [����������� ������� 12, n -- ����� �����]
*/
float** createMatrix(float * x, float * f){
    float ** matrix = new float*[s];
    /// ����������������� ������� ������
    for(int i = 0; i < s; i++){
        matrix[i] = new float[s];
        for(int j = 0; j < s; j++){
            matrix[i][j] = 0;
        }
    }
    /** ������ 2*n - 2 ����� ����� ���������������
        �������� ���������� �������� � ������ ������������
        c ���������� �������� �������
    */
    int m_0 = 0;
    int A_0 = n;
    int B_0 = 2*n - 1;
    for(int i = 0; i < n - 1; i++){
        /// <0.5*x[i]*x[i]> * m_i + x[i] * A_i + B_i = f[i]
        matrix[2*i][m_0 + i] = 0.5*x[i]*x[i];
        matrix[2*i][A_0 + i] = x[i];
        matrix[2*i][B_0 + i] = 1;
        /** <1/6 * (3*x[i+1]*x[i+1] - {x[i+1] - x[i]}^2)> * m_i +
            <1/6 * {x[i+1] - x[i]}^2> * m_(i+1) +
            x[i+1] * A_i + B_i = f[i + 1]
        */
        float dx2 = x[i+1] - x[i];
        dx2*=dx2;
        matrix[2*i + 1][m_0 + i] = (3*x[i+1]*x[i+1] - dx2) / 6.0;
        matrix[2*i + 1][m_0 + i + 1] = dx2 / 6.0;
        matrix[2*i + 1][A_0 + i] = x[i+1];
        matrix[2*i + 1][B_0 + i] = 1;
    }
    /** ��������� n - 2 ����� -- ������� ����������
        ������ ����������� � ��������� ������:
        <0.5*(x[i] + x[i+1])> * m_(i+1) +
        <-0.5*(x[i] + x[i+1])> * m_i + A_(i+1) - A_i = 0
    */
    int offset = 2*n - 2;
    for(int i = 0; i < n - 2; i++){
        float k = 0.5*(x[i] + x[i+1]);
        matrix[offset + i][m_0 + i + 1] = k;
        matrix[offset + i][m_0 + i] = -k;
        matrix[offset + i][A_0 + i + 1] = 1;
        matrix[offset + i][A_0 + i] = -1;
    }
    /** ��������� ��� ������ -- ����� ������
        ����������� ����� ����� ����� x_0 � x_n
        ��������������: ���������� ������� m_0 � m_(n-1) */
    matrix[3*n - 4][m_0] = 1;
    matrix[3*n - 3][m_0 + n - 1] = 1;
    return matrix;
}

/// ���������� ������� ���������� ������ ��� ������ ������
float* createVector(float * f,
                    float secondDerivativeInFirstPoint,
                    float secondDerivativeInLastPoint){
    /** ������ 2*n - 2 ����� ����� ���������������
        �������� ���������� �������� � ������ ������������
        c ���������� �������� �������:
        ��������� ����� � ��� ����� ����� ��������������� ���������
        �������� ������� � ������ ����������������
    */
    float * vector = new float[s];
    vector[0] = f[0];
    vector[2*n - 3] = f[n - 1];
    for(int i = 1; i < n - 1; i++){
        vector[2*i - 1] = f[i];
        vector[2*i] = f[i];
    }
    /** ��������� n - 2 ����� -- ������� ����������
        ������ ����������� � ��������� ������:
        ��������� ����� ����� 0
    */
    for(int i = 2*n - 2; i < 3*n - 4; i++){
        vector[i] = 0;
    }
    /** ��������� ��� ������ -- ����� ������
        ����������� ����� ����� ����� x_0 � x_n
        ��������������:
        ��������� ����� ���������� � ����� */
    vector[3*n - 4] = secondDerivativeInFirstPoint;
    vector[3*n - 3] = secondDerivativeInLastPoint;
    return vector;
}
/// �������� ��� ������ ������
float* backSubstitution(float ** matrix, float * vector){
    float * result = new float[s];
    float temp_sum = 0;
    for(int i = s - 1; i  >= 0; i--){
        temp_sum = 0;
        result[i] = vector[i];
        for(int j = i + 1; j < s; j++){
            result[i] -= matrix[i][j] * result[j];
        }
        result[i] /= matrix[i][i];
    }
    return result;
}
///����� �������� �������� �� �������
///������ ������� � ������� ��������� ������ �������, � ������� �����
///������� ������� �������
int chooseLeadingElement(float ** matrix, float * vector, int index){
    int maxrow = index;
    float temp;
    ///���� �� ������� � ���� ������ ������������� ��������
    for(int i = index + 1; i < s; i++){
        temp = matrix[i][index];
        if(temp > matrix[maxrow][index]) maxrow = i;
    }
    return maxrow;
}
///�������� ������� fi-� i si-� ����� ����������� �������
void swapLines(float ** matrix, float * vector, int fi, int si){
    if(fi != si){
        float temp = vector[fi];
        vector[fi] = vector[si];
        vector[si] = temp;
        for(int i = 0; i < s; i++){
            temp = matrix[fi][i];
            matrix[fi][i] = matrix[si][i];
            matrix[si][i] = temp;
        }
    }
}
///������ ��� ������ ������
/// ������� �������� ����������, ��� ���������� ������ ������������
/// true - c ������� ��������
/// false (�� ���������) - ���
void forwardElimantion(float ** matrix, float * vector,
                       bool with_choosing_leading_element = false){
    float l;
    ///��� �� ������� �������
    for(int a = 0; a < s - 1; a++){
        ///��� ����� ����������, ���� ���������� ����� ������ � ������� ��������
        if(with_choosing_leading_element){
            ///���� ������ �������� �������� � a-� �������
            int le_index = chooseLeadingElement(matrix, vector, a);
            ///������ ������� a-� ������ � ������, ���������� ������� �������
            swapLines(matrix, vector, a, le_index);
        }
        ///����� � ������ ���������� ������ 1(a,b)
        for(int b = a + 1; b < s; b++){
            l = matrix[b][a] / matrix[a][a];
            vector[b] -= l*vector[a];
            matrix[b][a] = 0;
            for(int c = a + 1; c < s; c++){
                matrix[b][c] -= l*matrix[a][c];
            }
        }
    }
}
/// ���������� �������� ������� � ����� point
float computeSplineValue(float point, float * solution, float * x){
    /**���� ���������� � ������� �������� ����� point:
        ����� ���������� �����:  x[i-1] <= point <= x[i]
    */
    int i = 0;
    do{
        if(x[++i] > point) break;
    }while (i < n);
    /** ��������� �������� ���������������� ���������� � ����� point:
        S(point) = {m_i - m_(i-1)} / (6*{x[i] - x[i - 1]}) * {point - x[i - 1]}^3 +
                0.5* m_(i-1) * point^2 + A_(i-1)* point + B_(i-1)
    */
    int m_0 = 0;
    int A_0 = n;
    int B_0 = 2*n - 1;
    float S = (solution[m_0 + i] - solution[m_0 + i - 1]) /
                (6.0*(x[i] - x[i - 1]));
    float delta3 = point - x[i - 1];
    delta3 *= (delta3*delta3);
    S*= delta3;
    S += 0.5 * solution[m_0 + i - 1] * point * point;
    S += solution[A_0 + i - 1] * point;
    S += solution[B_0 + i - 1];
    return S;
}
int main()
{
    ///�������� ������ �� �������:
    ///(�������� ��������� �������� ������ ��� ������� ����������� � ������� �)
    float * x = new float[n]{0, 1, 2, 3, 4};
    float * f = new float[n]{0, 0.5, 0.86603, 1, 0.86603};
    /// �������������� �������: �������� ������ ����������� � ������ � ��������� �����
    float secondDerivativeInFirstPoint = 0;
    float secondDerivativeInLastPoint = 0;
    ///����� �������� �������� ������� � �����:
    float point = 1.5;
    /** ������  ������� matrix
        � ������� ��������� ������ vector
        ��� ������ ������
        ����� ��������� ����������� � ��������������� �������
    */
    float ** matrix = createMatrix(x, f);
    float * vector = createVector(f,secondDerivativeInFirstPoint, secondDerivativeInLastPoint);
    /// ������ ��� ������ ������
    forwardElimantion(matrix, vector, true);
    /// �������� ��� ������ ������
    float * solution = backSubstitution(matrix, vector);
    /// ���������� �������� ������� �� ����������� ������ ������
    cout << "Spline value at x = "<<point<<":\n";
    cout <<computeSplineValue(point, solution, x);
    return 0;
}
