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
/// вывод матрицы в консоль
void printMatrix(std::vector<std::vector<float>> matrix,
                 int a = DEF_WIDTH){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cout << std::setw(a) << matrix[i][j];
        }
        std::cout <<'\n';
    }
}
/// вывод вектора в консоль
void printVector(std::vector<float> v,
                 int a = DEF_WIDTH){
    for(int i = 0; i < n; i++){
        std::cout << std::setw(a) << v[i];
        std::cout << '\n';
    }
}

/// создание матрицы
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
/// вспомогательный метод вычисления произведения матрицы на вектор
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
/// скалярное произведение векторов x и y
float scalarProduct(std::vector<float> x, std::vector<float> y){
    float result = 0;
    for(int i = 0; i < n; i++){
        result += x[i]*y[i];
    }
    return result;
}
/** вычисление максимум-нормы вектора x */
float maximumNorm(std::vector<float> x){
    int index = 0;
    for(int i = 1; i < n; i++){
        if(fabs(x[index]) < fabs(x[i])){
            index = i;
        }
    }
    return fabs(x[index]);
}

/// нормализация вектора x
std::vector<float> normalize(std::vector<float> x){
    std::vector<float> result(n, 0);
    float norm = maximumNorm(x);
    for(int i = 0; i < n; i++){
        result[i] = x[i] / norm;
    }
    return result;
}

/** вычисление приближенного НАИБОЛЬШЕГО собственного значения
    для двух векторов, один из которых является НОРМИРОВАННЫМ вектором
    k-й итерации, а второй -- вектором (k+1)-й итерации
*/
float firstDominantEigenvalueApproximation(
                                    std::vector<float> prevIterNormalizedVector,
                                    std::vector<float> currentIterVector){
    /** идём по всем координатам НОРМИРОВАННОГО вектора более ранней
        итерации, находим индекс наибольшей по модулю координаты
    */
    int index = 0;
    for(int i = 1; i < n; i++){
        if(fabs(prevIterNormalizedVector[index]) <
           fabs(prevIterNormalizedVector[i])){
            index = i;
        }
    }
    /** получаем знак наибольшей по модулю координаты (index)
        НОРМИРОВАННОГО вектора более ранней итерации */
    float sign = (prevIterNormalizedVector[index] > 0) -
                    (prevIterNormalizedVector[index] < 0);
    /** находим приближённое наибольшее собственное значение
        по Формуле 2

    */
    return currentIterVector[index] * sign;
}

/** ТОЛЬКО ДЛЯ СИММЕТРИЧНОЙ МАТРИЦЫ:
    вычисление приближенного НАИБОЛЬШЕГО собственного значения
    для двух векторов, один из которых является НОРМИРОВАННЫМ вектором
    k-й итерации, а второй -- вектором (k+1)-й итерации
*/
float firstDominantEigenvalueApproximationForSymmetricMatrix(
                                    std::vector<float> prevIterNormalizedVector,
                                    std::vector<float> currentIterVector){
    /** находим приближённое наибольшее собственное значение
        по Формуле 3
    */
    return scalarProduct(currentIterVector, prevIterNormalizedVector) /
            scalarProduct(prevIterNormalizedVector, prevIterNormalizedVector);
}
/** приближённое вычисление собственного вектора, соответствующего
    ВТОРОМУ НАИБОЛЬШЕМУ собственному значению
*/
std::vector<float> eigenvectorOfSecondDominantEigenvalueApproximation(
                                std::vector<float> prevIterNormalizedVector,
                                std::vector<float> currentIterVector,
                                float firstDominantEigenvalue){
    ///вычисляем вектор по Формуле 6
    std::vector<float> eigenvector(n);
    for(int i = 0; i < n; i++){
        eigenvector[i] = currentIterVector[i] -
                        firstDominantEigenvalue * prevIterNormalizedVector[i];
    }
    return eigenvector;
}
/** вычисление погрешности вычисления НАИБОЛЬШЕГО собственного значения
    для двух векторов, один из которых является НОРМИРОВАННЫМ вектором
    k-й итерации, а второй -- вектором (k+1)-й итерации
*/
float firstDominantEigenvalueError(std::vector<float> prevIterNormalizedVector,
                                   std::vector<float> currentIterVector,
                                   float firstDominantEigenvalue){
    /**
        В силу того, что Формула 4 возвращает норму вектора, который вычисляется
        по Формуле 6, используем метод приближённого вычисления
        собственного вектора, соответствующего ВТОРОМУ НАИБОЛЬШЕМУ
        собственному значению
    */
    std::vector<float> temp =eigenvectorOfSecondDominantEigenvalueApproximation(
                                                    prevIterNormalizedVector,
                                                    currentIterVector,
                                                    firstDominantEigenvalue);
    /// возвращаем максимум-норму данного вектора (Формула 4)
    return maximumNorm(temp);
}
/** вычисление приближенного ВТОРОГО НАИБОЛЬШЕГО собственного значения
    для трёх векторов, 1-ый из которых является НОРМИРОВАННЫМ вектором
    (m-1)-й итерации, второй -- вектором m-й итерации, третий --
    вектором (m+1)-й итерации
*/
float secondDominantEigenvalueApproximation(
                                std::vector<float> prevIterNormalizedVector,
                                std::vector<float> currentIterVector,
                                std::vector<float> nextIterVector,
                                float firstDominantEigenvalue){
    /** В силу того, что Формула 5 использует вектор, который вычисляется
        по Формуле 6, используем метод приближённого вычисления
        собственного вектора, соответствующего ВТОРОМУ НАИБОЛЬШЕМУ
        собственному значению.
    */
    int index = 0;
    std::vector<float> currentEigenVector =
                            eigenvectorOfSecondDominantEigenvalueApproximation(
                                                    prevIterNormalizedVector,
                                                    currentIterVector,
                                                    firstDominantEigenvalue);
    /// найдём номер наибольшей по модулю координаты вычисленного вектора
    for(int i = 1; i < n; i++){
        if(fabs(currentEigenVector[index]) <
           fabs(currentEigenVector[i])){
            index = i;
        }
    }
    /// считаем норму вектора v_m
    float normOfCurrentIterVector = maximumNorm(currentIterVector);
    /** вычисляем ВТОРОЕ НАИБОЛЬШЕЕ собственное значение по Формуле 5
    */
    float result = (nextIterVector[index] * normOfCurrentIterVector -
                    firstDominantEigenvalue * currentIterVector[index]) /
                    currentEigenVector[index];
    return result;
}
/// погрешность ВТОРОГО НАИБОЛЬШЕГО собственного значения
float secondDominantEigenvalueError(const vector<vector<float>>& matrix,
                                   const std::vector<float>& eigenvector,
                                   const float& secondDominantEigenvalue){
    ///вычисляем по Формуле 7:
    vector<float> temp = matrixVectorProduct(matrix, eigenvector);
    for(int i = 0; i < n; i++){
        temp[i] -= secondDominantEigenvalue*eigenvector[i];
    }
    return maximumNorm(temp);
}
/// степенной метод
void powerMethod(const std::vector<std::vector<float>>& matrix){
    /// начальное значение вектора
    std::vector<float> u(n, 0);
    /// вспомогательный вектор
    std::vector<float> v(n, 0);
    v[0] = 1;
    float l_1_common, l_1_symmetric;
    /// векторы, необходимые для последующего вычисления lambda_2;
    std::vector<float> u_29(n, 0), v_30(n, 0), v_31(n, 0);
    std::vector<float> u_49(n, 0), v_50(n, 0), v_51(n, 0);
    /// итерационное вычисления (по Формуле 1):
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
            cout << "\nИТЕРАЦИЯ k = " << k << "\n\n";
            cout << "   Собственный вектор, соответствующий lambda_1:\n\n";
            printVector(u);
            cout << "\n    Приближённое собственное значение lambda_1:\n\n";
            l_1_common = firstDominantEigenvalueApproximation(u,v);
            l_1_symmetric =
                    firstDominantEigenvalueApproximationForSymmetricMatrix(u,v);
            cout << "       a) По общей формуле: \n\n";
            cout << setprecision(DEF_WIDTH) << l_1_common << "\n\n";
            cout << "\n       б) По формуле для симметрических: \n\n";
            cout << setprecision(DEF_WIDTH) << l_1_symmetric << "\n\n";
            cout << "---------------------------------------------------------";
        }
     }
     cout << "\nНОРМА ВЕКТОРА v_k+1 - lambda_1*u_k:\n\n";
     cout << "\n    a) вычисленного по общей формуле: \n\n";
     float commonError = firstDominantEigenvalueError(u, v, l_1_common);
     cout << setprecision(DEF_WIDTH) << commonError << "\n\n";
     cout << "\n    б) вычисленного по формуле для симметричных матриц : \n\n";
     float symmetricError = firstDominantEigenvalueError(u, v, l_1_symmetric);
     cout << setprecision(DEF_WIDTH) << symmetricError << "\n\n";
     cout << "\n\n---------------------------------------------------------";
     float l_2, error_2;
     vector<float> v_2(n, 0);

     cout << "\nСЛУЧАЙ 1. ВЫЧИСЛЕНИЕ lambda_2 для m = 30, k=50,\n lambda_1 ";
     cout << "посчитано по общей формуле:\n\n";
     l_2 = secondDominantEigenvalueApproximation(u_29, v_30, v_31,
                                                       l_1_common);
     cout << "\n    Приближённое собственное значение lambda_2: \n";
     cout << setprecision(DEF_WIDTH) << l_2 << "\n\n";
     cout << "\n    Собственный вектор, соответствующий lambda_2:\n\n";
     v_2 = eigenvectorOfSecondDominantEigenvalueApproximation(u, v,
                                                              l_1_common);
     printVector(v_2);
     cout << "\n    Норма вектора Ax - lambda_2*x: \n\n";
     error_2 = secondDominantEigenvalueError(matrix, v_2, l_2);
     cout << setprecision(DEF_WIDTH) << error_2 << "\n\n";
     cout << "\n---------------------------------------------------------";

     cout << "\nСЛУЧАЙ 2. ВЫЧИСЛЕНИЕ lambda_2 для m = 50, k=50,\n lambda_1 ";
     cout << "посчитано по общей формуле:\n\n";
     l_2 = secondDominantEigenvalueApproximation(u_49, v_50, v_51,
                                                       l_1_common);
     cout << "\n    Приближённое собственное значение lambda_2: \n\n";
     cout << setprecision(DEF_WIDTH) << l_2 << "\n\n";
     cout << "\n    Собственный вектор, соответствующий lambda_2 аналогичен\n\n";
     cout << "\n    Норма вектора Ax - lambda_2*x: \n\n";
     error_2 = secondDominantEigenvalueError(matrix, v_2, l_2);
     cout << setprecision(DEF_WIDTH) << error_2 << "\n\n";
     cout << "\n---------------------------------------------------------";

     cout << "\nСЛУЧАЙ 3. ВЫЧИСЛЕНИЕ lambda_2 для m = 50, k=50,\n lambda_1 ";
     cout << "посчитано по формуле для симметричных матриц:\n\n";
     l_2 = secondDominantEigenvalueApproximation(u_49, v_50, v_51,
                                                       l_1_symmetric);
     cout << "\n    Приближённое собственное значение lambda_2: \n\n";
     cout << setprecision(DEF_WIDTH) << l_2 << "\n\n";
     cout << "\n    Собственный вектор, соответствующий lambda_2:\n\n";
     v_2 = eigenvectorOfSecondDominantEigenvalueApproximation(u, v,
                                                              l_1_symmetric);
     printVector(v_2);
     cout << "\n    Норма вектора Ax - lambda_2*x: \n\n";
     error_2 = secondDominantEigenvalueError(matrix, v_2, l_2);
     cout << setprecision(DEF_WIDTH) << error_2 << "\n\n";
     cout << "\n---------------------------------------------------------";

}
int main()
{
    setlocale(0, "Russian");
    std::vector<std::vector<float>> matrix = createMatrix();
    cout << "Матрица: \n";
    printMatrix(matrix, 5);
    cout <<"\n\n";
    powerMethod(matrix);
    return 0;
}
