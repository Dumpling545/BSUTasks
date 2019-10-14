#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;

float k = 0;/// int k = 1 ��� ������ 1b
int m = 12;
int n = 14;
const int DEF_WIDTH = 32;
/// ����� ������� � �������
void printMatrix(float ** matrix, int a = DEF_WIDTH){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << std::setw(a) << matrix[i][j];
        }
        cout <<'\n';
    }
}
/// ����� ������� � �������
void printVector(float * vector, int a = DEF_WIDTH){
    for(int i = 0; i < n; i++){
        cout << std::setw(a) << vector[i];
        cout << '\n';
    }
}
/// ��������� �������
float** createMatrix(){
    srand (time(NULL));
    float temp_sum = 0;
    float ** matrix = new float*[n];
    for(int i = 0; i < n; i++){
        matrix[i] = new float[n];
        temp_sum = 0;
        for(int j = 0; j < n; j++){
            matrix[i][j] = -rand()%5;
            temp_sum += matrix[i][j];
        }
        matrix[i][i] -= temp_sum;
    }
    matrix[0][0] += pow(10.0 , -k);
    return matrix;
}
/// �������� ������� ��������� �������� �� ������� (� ������� x �������)
float* createVector(float ** matrix){
    float * vector = new float[n];
    for(int i = 0; i < n; i++){
        vector[i] = 0;
        for(int j = 0; j < n; j++){
            vector[i]+= matrix[i][j]*(m + j);
        }
    }
    return vector;
}
/// ������ ��� ������ ������ ��� ������ �������� ��������
void forwardElimantion(float ** matrix, float * vector){
    float l;
    ///��� �� ������� �������
    for(int a = 0; a < n - 1; a++){
        ///��� �� ���� �������, ��������� �� a-� �������
        for(int b = a + 1; b < n; b++){
            /// ��������� ����������� l ��� b-� ������
            l = matrix[b][a] / matrix[a][a];
            ///�������� a-� ������ ����������� �������,
            ///���������� �� ���������� l, �� b-� ������
            vector[b] -= l*vector[a];
            matrix[b][a] = 0;
            for(int c = a + 1; c < n; c++){
                matrix[b][c] -= l*matrix[a][c];
            }
        }
        ///����� � ������� ������� ����� ������ �������� ������ ������
        if(a == 0){
            cout << "\n\n Matrix after first step of forward elimination:\n";
            printMatrix(matrix);
        }
    }
}
///�������� ��� ������ ������
float* backSubstitution(float ** matrix, float * vector){
    float * result = new float[n];
    ///��� �� ������� ��������������� ������� � �������� �����������,
    ///�������� �� ������ ���� ���� �� ��������� ������� �������
    for(int i = n - 1; i  >= 0; i--){
        result[i] = vector[i];
        for(int j = i + 1; j < n; j++){
            result[i] -= matrix[i][j] * result[j];
        }
        result[i] /= matrix[i][i];
    }
    return result;
}
///���������� ������������� ������ ������ ������ ��� ������ ��������-�����
float relativeError(float * result){
    float max_delta = abs(result[0] - m);
    float temp;
    for(int i = 1; i < n; i++){
        temp = abs(result[i] - m - i);
        if(temp > max_delta) max_delta = temp;
    }
    return max_delta / (m + n - 1);
}
///����������� �������
float ** copyMatrix(float ** matrix){
    float ** copy = new float*[n];
    for(int i = 0; i < n ; i++){
        copy[i] = new float[n];
        for(int j = 0; j < n; j++){
            copy[i][j] = matrix[i][j];
        }
    }
    return copy;
}
///����������� �������
float * copyVector(float * vector){
    float * copy = new float[n];
    for(int i = 0; i < n; i++){
        copy[i] = vector[i];
    }
    return copy;
}
int main()
{
    ///�������� � ����� ������� ������
    cout << "Input:\n\n Matrix:\n";
    float ** matrix = createMatrix();
    float ** copy_matrix = copyMatrix(matrix);
    printMatrix(matrix, 4);
    cout << "\n\n Vector:\n";
    float * vector = createVector(matrix);
    printVector(vector,6);
    ///������� ����: ������ ���
    forwardElimantion(matrix, vector);
    ///������� ����: �������� ���
    float * result = backSubstitution(matrix, vector);
    ///����� ����������
    cout << "\n\nResult:\n";
    printVector(result);
    ///����� ������
    cout << "\n\nRelative Error: "<<setprecision(DEF_WIDTH) << relativeError(result);
    ///��������� ����������� �������� ��� k = 1
    cout << "\n\n...................................................................................................\n";
    cout << "WITH K=1:\n\n";
    ///�������� ������������� ������� ���, ����� ��� ��������������� k = 1
    copy_matrix[0][0]-=pow(10.0 , -k);
    k = 1;
    copy_matrix[0][0]+=pow(10.0 , -k);
    cout << "Input:\n\n Matrix:\n";
    printMatrix(copy_matrix);
    cout << "\n\n Vector:\n";
    ///������ ������ ��������� ������ ��� ����� �������
    float * vector1 = createVector(copy_matrix);
    printVector(vector1,6);
    forwardElimantion(copy_matrix, vector1);
    float * result1 = backSubstitution(copy_matrix, vector1);
    cout << "\n\nResult:\n";
    printVector(result1);
    cout << "\n\nRelative Error: "<<setprecision(DEF_WIDTH) << relativeError(result1);
    return 0;
}
