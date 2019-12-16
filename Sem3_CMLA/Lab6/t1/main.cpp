#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
using namespace std;

int n = 11;
const int DEF_WIDTH = 32;
int k_max = 50;
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

/// �������� �������
std::vector<std::vector<float>> createMatrix(){
    srand (time(NULL));
    float temp_sum = 0;
    std::vector<std::vector<float>> matrix(n);
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
    matrix[0][0] += 1;
    return matrix;
}
/// ��������������� ����� ���������� ������������ ������� �� ������
std::vector<float> matrixVectorProduct(std::vector<std::vector<float>> matrix,
                                  std::vector<float> vect){
    std::vector<float> result(n, 0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            result[i] += matrix[i][j]*vect[j];
        }
    }
    return result;
}
/// ��������� ������������ �������� x � y
float scalarProduct(std::vector<float> x, std::vector<float> y){
    float result = 0;
    for(int i = 0; i < n; i++){
        result += x[i]*y[i];
    }
    return result;
}
/** ���������� ��������-����� ������� x */
float maximumNorm(std::vector<float> x){
    int index = 0;
    for(int i = 1; i < n; i++){
        if(fabs(x[index]) < fabs(x[i])){
            index = i;
        }
    }
    return fabs(x[index]);
}

/// ������������ ������� x
std::vector<float> normalize(std::vector<float> x){
    std::vector<float> result(n, 0);
    float norm = maximumNorm(x);
    for(int i = 0; i < n; i++){
        result[i] = x[i] / norm;
    }
    return result;
}

/** ���������� ������������� ����������� ������������ ��������
    ��� ���� ��������, ���� �� ������� �������� ������������� ��������
    k-� ��������, � ������ -- �������� (k+1)-� ��������
*/
float firstDominantEigenvalueApproximation(
                                    std::vector<float> prevIterNormalizedVector,
                                    std::vector<float> currentIterVector){
    /** ��� �� ���� ����������� �������������� ������� ����� ������
        ��������, ������� ������ ���������� �� ������ ����������
    */
    int index = 0;
    for(int i = 1; i < n; i++){
        if(fabs(prevIterNormalizedVector[index]) <
           fabs(prevIterNormalizedVector[i])){
            index = i;
        }
    }
    /** �������� ���� ���������� �� ������ ���������� (index)
        �������������� ������� ����� ������ �������� */
    float sign = (prevIterNormalizedVector[index] > 0) -
                    (prevIterNormalizedVector[index] < 0);
    /** ������� ����������� ���������� ����������� ��������
        �� ������� 2

    */
    return currentIterVector[index] * sign;
}

/** ������ ��� ������������ �������:
    ���������� ������������� ����������� ������������ ��������
    ��� ���� ��������, ���� �� ������� �������� ������������� ��������
    k-� ��������, � ������ -- �������� (k+1)-� ��������
*/
float firstDominantEigenvalueApproximationForSymmetricMatrix(
                                    std::vector<float> prevIterNormalizedVector,
                                    std::vector<float> currentIterVector){
    /** ������� ����������� ���������� ����������� ��������
        �� ������� 3
    */
    return scalarProduct(currentIterVector, prevIterNormalizedVector) /
            scalarProduct(prevIterNormalizedVector, prevIterNormalizedVector);
}
/** ����������� ���������� ������������ �������, ����������������
    ������� ����������� ������������ ��������
*/
std::vector<float> eigenvectorOfSecondDominantEigenvalueApproximation(
                                std::vector<float> prevIterNormalizedVector,
                                std::vector<float> currentIterVector,
                                float firstDominantEigenvalue){
    ///��������� ������ �� ������� 6
    std::vector<float> eigenvector(n);
    for(int i = 0; i < n; i++){
        eigenvector[i] = currentIterVector[i] -
                        firstDominantEigenvalue * prevIterNormalizedVector[i];
    }
    return eigenvector;
}
/** ���������� ����������� ���������� ����������� ������������ ��������
    ��� ���� ��������, ���� �� ������� �������� ������������� ��������
    k-� ��������, � ������ -- �������� (k+1)-� ��������
*/
float firstDominantEigenvalueError(std::vector<float> prevIterNormalizedVector,
                                   std::vector<float> currentIterVector,
                                   float firstDominantEigenvalue){
    /**
        � ���� ����, ��� ������� 4 ���������� ����� �������, ������� �����������
        �� ������� 6, ���������� ����� ������������ ����������
        ������������ �������, ���������������� ������� �����������
        ������������ ��������
    */
    std::vector<float> temp =eigenvectorOfSecondDominantEigenvalueApproximation(
                                                    prevIterNormalizedVector,
                                                    currentIterVector,
                                                    firstDominantEigenvalue);
    /// ���������� ��������-����� ������� ������� (������� 4)
    return maximumNorm(temp);
}
/** ���������� ������������� ������� ����������� ������������ ��������
    ��� ��� ��������, 1-�� �� ������� �������� ������������� ��������
    (m-1)-� ��������, ������ -- �������� m-� ��������, ������ --
    �������� (m+1)-� ��������
*/
float secondDominantEigenvalueApproximation(
                                std::vector<float> prevIterNormalizedVector,
                                std::vector<float> currentIterVector,
                                std::vector<float> nextIterVector,
                                float firstDominantEigenvalue){
    /** � ���� ����, ��� ������� 5 ���������� ������, ������� �����������
        �� ������� 6, ���������� ����� ������������ ����������
        ������������ �������, ���������������� ������� �����������
        ������������ ��������.
    */
    int index = 0;
    std::vector<float> currentEigenVector =
                            eigenvectorOfSecondDominantEigenvalueApproximation(
                                                    prevIterNormalizedVector,
                                                    currentIterVector,
                                                    firstDominantEigenvalue);
    /// ����� ����� ���������� �� ������ ���������� ������������ �������
    for(int i = 1; i < n; i++){
        if(fabs(currentEigenVector[index]) <
           fabs(currentEigenVector[i])){
            index = i;
        }
    }
    /// ������� ����� ������� v_m
    float normOfCurrentIterVector = maximumNorm(currentIterVector);
    /** ��������� ������ ���������� ����������� �������� �� ������� 5
    */
    float result = (nextIterVector[index] * normOfCurrentIterVector -
                    firstDominantEigenvalue * currentIterVector[index]) /
                    currentEigenVector[index];
    return result;
}
/// ����������� ������� ����������� ������������ ��������
float secondDominantEigenvalueError(const vector<vector<float>>& matrix,
                                   const std::vector<float>& eigenvector,
                                   const float& secondDominantEigenvalue){
    ///��������� �� ������� 7:
    vector<float> temp = matrixVectorProduct(matrix, eigenvector);
    for(int i = 0; i < n; i++){
        temp[i] -= secondDominantEigenvalue*eigenvector[i];
    }
    return maximumNorm(temp);
}
/// ��������� �����
void powerMethod(const std::vector<std::vector<float>>& matrix){
    /// ��������� �������� �������
    std::vector<float> u(n, 0);
    /// ��������������� ������
    std::vector<float> v(n, 0);
    v[0] = 1;
    float l_1_common, l_1_symmetric;
    /// �������, ����������� ��� ������������ ���������� lambda_2;
    std::vector<float> u_29(n, 0), v_30(n, 0), v_31(n, 0);
    std::vector<float> u_49(n, 0), v_50(n, 0), v_51(n, 0);
    /// ������������ ���������� (�� ������� 1):
    for(int k = 0; k <= k_max; k++){
        /// u(k) ::=  v(k) / norm(v(k))
        u = normalize(v);
        v.clear();
        /// v(k+1) ::=  A*u(k)
        v = matrixVectorProduct(matrix, u);
        if(k == 29){
            u_29.assign(u.begin(), u.end());
            v_30.assign(v.begin(), v.end());
        } else if(k == 30){
            v_31.assign(v.begin(), v.end());
        }else if(k == 49){
            u_49.assign(u.begin(), u.end());
            v_50.assign(v.begin(), v.end());
        } else if(k == 50){
            v_51.assign(v.begin(), v.end());
        }
        if(k >= 46){
            cout << "\n�������� k = " << k << "\n\n";
            cout << "   ����������� ������, ��������������� lambda_1:\n\n";
            printVector(u);
            cout << "\n    ����������� ����������� �������� lambda_1:\n\n";
            l_1_common = firstDominantEigenvalueApproximation(u,v);
            l_1_symmetric =
                    firstDominantEigenvalueApproximationForSymmetricMatrix(u,v);
            cout << "       a) �� ����� �������: \n\n";
            cout << setprecision(DEF_WIDTH) << l_1_common << "\n\n";
            cout << "\n       �) �� ������� ��� ��������������: \n\n";
            cout << setprecision(DEF_WIDTH) << l_1_symmetric << "\n\n";
            cout << "---------------------------------------------------------";
        }
     }
     cout << "\n����� ������� v_k+1 - lambda_1*u_k:\n\n";
     cout << "\n    a) ������������ �� ����� �������: \n\n";
     float commonError = firstDominantEigenvalueError(u, v, l_1_common);
     cout << setprecision(DEF_WIDTH) << commonError << "\n\n";
     cout << "\n    �) ������������ �� ������� ��� ������������ ������ : \n\n";
     float symmetricError = firstDominantEigenvalueError(u, v, l_1_symmetric);
     cout << setprecision(DEF_WIDTH) << symmetricError << "\n\n";
     cout << "\n\n---------------------------------------------------------";
     float l_2, error_2;
     vector<float> v_2(n, 0);

     cout << "\n������ 1. ���������� lambda_2 ��� m = 30, k=50,\n lambda_1 ";
     cout << "��������� �� ����� �������:\n\n";
     l_2 = secondDominantEigenvalueApproximation(u_29, v_30, v_31,
                                                       l_1_common);
     cout << "\n    ����������� ����������� �������� lambda_2: \n";
     cout << setprecision(DEF_WIDTH) << l_2 << "\n\n";
     cout << "\n    ����������� ������, ��������������� lambda_2:\n\n";
     v_2 = eigenvectorOfSecondDominantEigenvalueApproximation(u, v,
                                                              l_1_common);
     printVector(v_2);
     cout << "\n    ����� ������� Ax - lambda_2*x: \n\n";
     error_2 = secondDominantEigenvalueError(matrix, v_2, l_2);
     cout << setprecision(DEF_WIDTH) << error_2 << "\n\n";
     cout << "\n---------------------------------------------------------";

     cout << "\n������ 2. ���������� lambda_2 ��� m = 50, k=50,\n lambda_1 ";
     cout << "��������� �� ����� �������:\n\n";
     l_2 = secondDominantEigenvalueApproximation(u_49, v_50, v_51,
                                                       l_1_common);
     cout << "\n    ����������� ����������� �������� lambda_2: \n\n";
     cout << setprecision(DEF_WIDTH) << l_2 << "\n\n";
     cout << "\n    ����������� ������, ��������������� lambda_2 ����������\n\n";
     cout << "\n    ����� ������� Ax - lambda_2*x: \n\n";
     error_2 = secondDominantEigenvalueError(matrix, v_2, l_2);
     cout << setprecision(DEF_WIDTH) << error_2 << "\n\n";
     cout << "\n---------------------------------------------------------";

     cout << "\n������ 3. ���������� lambda_2 ��� m = 50, k=50,\n lambda_1 ";
     cout << "��������� �� ������� ��� ������������ ������:\n\n";
     l_2 = secondDominantEigenvalueApproximation(u_49, v_50, v_51,
                                                       l_1_symmetric);
     cout << "\n    ����������� ����������� �������� lambda_2: \n\n";
     cout << setprecision(DEF_WIDTH) << l_2 << "\n\n";
     cout << "\n    ����������� ������, ��������������� lambda_2:\n\n";
     v_2 = eigenvectorOfSecondDominantEigenvalueApproximation(u, v,
                                                              l_1_symmetric);
     printVector(v_2);
     cout << "\n    ����� ������� Ax - lambda_2*x: \n\n";
     error_2 = secondDominantEigenvalueError(matrix, v_2, l_2);
     cout << setprecision(DEF_WIDTH) << error_2 << "\n\n";
     cout << "\n---------------------------------------------------------";

}
int main()
{
    setlocale(0, "Russian");
    std::vector<std::vector<float>> matrix = createMatrix();
    cout << "�������: \n";
    printMatrix(matrix, 5);
    cout <<"\n\n";
    powerMethod(matrix);
    return 0;
}
