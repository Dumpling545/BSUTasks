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

const int n = 3;
const int DEF_WIDTH = 32;
const float epsilon = 1e-8;
/// ����� ������� � �������
void printMatrix(std::vector<std::vector<float>> matrix,
                 int a = DEF_WIDTH){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cout << std::setw(a) << matrix[i][j];
        }
        std::cout <<'\n';
    }
}
/// ����� ������� � �������
void printVector(std::vector<float> v,
                 int a = DEF_WIDTH){
    for(int i = 0; i < n; i++){
        std::cout << std::setw(a) << v[i];
        std::cout << '\n';
    }
}
/// ���������� ����� �������
float trace(std::vector<std::vector<float>> matrix){
    float result = 0;
    for(int i = 0; i < n; i++){
        result += matrix[i][i];
    }
    return result;
}
/// �������� �������
std::vector<std::vector<float>> createMatrix(){
    srand(time(NULL));
    std::vector<float> nullvector(n, 0);
    std::vector<std::vector<float>> matrix(n, nullvector);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = rand()%101 - 50;
        }
    }
    return matrix;
}

/// ��������������� ����� ��� ���������� ������ �_n-1, M_n-2,..., M_1
std::vector<std::vector<float>> computeM_k(
                                  const std::vector<std::vector<float>> &matrix,
                                  int k){
    /// ������ ������� m_k � ��������� � ������ (�������������).
    std::vector<float> nullvector(n, 0);
    std::vector<std::vector<float>> m_k(n, nullvector);
    /** ��������� ������� ��������� ���������,
        a k-� ������ -- ���������� {-matrix[k + 1][i] / matrix[k+1][k]}.
        ������� �� ����� {m_k[k][k]} ��������� ��� {1 / matrix[k+1][k]}*/
    for(int i = 0; i < n; i++){
        m_k[i][i] = 1;
        m_k[k][i] = - matrix[k + 1][i] / matrix[k+1][k];
    }
    m_k[k][k] = 1 / matrix[k+1][k];
    return m_k;
}

/** ��������������� ����� ��� ���������� ������ INVERSE(�_n-1),
                                                INVERSE(M_n-2),
                                                ...,
                                                INVERSE(M_1)*/
std::vector<std::vector<float>> computeInverseM_k(
                                  const std::vector<std::vector<float>> &matrix,
                                  int k){
    /// ������ ������� inverse_m_k � ��������� � ������ (�������������).
    std::vector<float> nullvector(n, 0);
    std::vector<std::vector<float>> inverse_m_k(n, nullvector);
    /** ��������� ������� ��������� ���������,
        a k-� ������ -- ���������� k+1 ������ ������� matrix*/
    for(int i = 0; i < n; i++){
        inverse_m_k[i][i] = 1;
        inverse_m_k[k][i] = matrix[k + 1][i];
    }
    return inverse_m_k;
}
/**��������������� ����� ��� ��������� ������ ������� n*n(�����) � n*n(������)*/
std::vector<std::vector<float>> matrixProduct(
                                const std::vector<std::vector<float>> &left,
                                const std::vector<std::vector<float>> &right){
    /// ������ ������� product � ��������� � ������ (�������������).
    std::vector<float> nullvector(n, 0);
    std::vector<std::vector<float>> product(n, nullvector);
    float sum;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            sum = 0;
            for(int s = 0; s < n; s++){
                sum += left[i][s] * right[s][j];
            }
            product[i][j] = sum;
        }
    }
    return product;
}

/** ���������� � ������������ ����� ���������� (���) ������� ������������.
    ���� � ���� ���������� ��� ���������, ��� ������ ��������������,
    ����� ���������� � ����������� false*/
bool danilevskijMethod(std::vector<std::vector<float>> &matrix){
    bool result = true;
    /** ��������������� ��������� ������� M_k, INVERSE(M_k) � A_(n-1-k)
        ��� A_(n-1-k) ::= INVERSE(M_k) * A_(n-1-{k+1}) * M_k; A_0 = matrix.
        ����������: �.�. ������� ����� � �������� ��������, �� �� ���� �������
        �� M_(n-2) �� M_0*/
    for(int k = n-2; k >= 0; k--){
        /** ���� ��������� ������� ������� ������ epsilon, �� �� �������
            ��� ����, � ������ ������ ������������ -- ������������.
            ������� �� ������, ��������� false*/
        if(abs(matrix[k+1][k]) < epsilon){
            std::cout << "\nUNREGULAR CASE!!!\n";
            result = false;
            break;
        }
        /// ����� ����� (�� ������� ����, �� ���� ����) ���������� ������.
        else {
            /// ��������� M_k, INVERSE(M_k) ��� ������� ����
            std::vector<std::vector<float>> m_k = computeM_k(matrix, k);
            std::vector<std::vector<float>> inverse_m_k =
                                                computeInverseM_k(matrix, k);
            /// ������� M_k � �������
             std::cout << "\n----------------------------------------\n";
             std::cout << "Matrix M_" << k+1 <<":\n";
             printMatrix(m_k);
            /// ��������� ����� ������� �� ������� ����
            matrix = matrixProduct(inverse_m_k, matrixProduct(matrix, m_k));
        }
    }
    return result;
}
int main()
{
    bool success = true;
    float tr = 0;
    /** ���� ����� �����������, ���� �� �� ������� ���������� ������ ������
        ������������.
    */
    std::vector<std::vector<float>> matrix;
        /// ������ � ������� �������
        matrix = {{ -0.6666666666, 2, -0.6666666666},
                  { 2, -0.3333333333, 1.3333333333},
                  { -0.6666666666, 1.3333333333, 1}};
        /// c������ ���� �������� �������
        tr = trace(matrix);
        std::cout << "\n----------------------------------------\n";
        std::cout << "Original matrix:\n";
        printMatrix(matrix);
        success = danilevskijMethod(matrix);
    /** ���� ��� ����������, ������ ���� ����� ������������
        ���� ���������� ������ ��� ������� �������.*/
    /// ������� ������������ ����� ����������, ���� ���. ������� � �����. p_1
    std::cout << "\n----------------------------------------\n";
    std::cout << "Frobenius normal form:\n";
    printMatrix(matrix);
    std::cout << "\n----------------------------------------\n";
    std::cout << "Trace of Frobenius normal form: ";
    std::cout << setprecision(DEF_WIDTH) << tr<<"\n";
    std::cout<<"Coefficient p_1: "<<setprecision(DEF_WIDTH)<<matrix[0][0]<<"\n";
    return 0;
}
