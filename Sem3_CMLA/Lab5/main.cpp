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
/// вычисление следа матрицы
float trace(std::vector<std::vector<float>> matrix){
    float result = 0;
    for(int i = 0; i < n; i++){
        result += matrix[i][i];
    }
    return result;
}
/// создание матрицы
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

/// Вспомогательный метод для вычисления матриц М_n-1, M_n-2,..., M_1
std::vector<std::vector<float>> computeM_k(
                                  const std::vector<std::vector<float>> &matrix,
                                  int k){
    /// Создаём матрицу m_k и заполняем её нулями (первоначально).
    std::vector<float> nullvector(n, 0);
    std::vector<std::vector<float>> m_k(n, nullvector);
    /** Заполняем главную диагональ единицами,
        a k-ю строку -- элементами {-matrix[k + 1][i] / matrix[k+1][k]}.
        Элемент на месте {m_k[k][k]} определим как {1 / matrix[k+1][k]}*/
    for(int i = 0; i < n; i++){
        m_k[i][i] = 1;
        m_k[k][i] = - matrix[k + 1][i] / matrix[k+1][k];
    }
    m_k[k][k] = 1 / matrix[k+1][k];
    return m_k;
}

/** Вспомогательный метод для вычисления матриц INVERSE(М_n-1),
                                                INVERSE(M_n-2),
                                                ...,
                                                INVERSE(M_1)*/
std::vector<std::vector<float>> computeInverseM_k(
                                  const std::vector<std::vector<float>> &matrix,
                                  int k){
    /// Создаём матрицу inverse_m_k и заполняем её нулями (первоначально).
    std::vector<float> nullvector(n, 0);
    std::vector<std::vector<float>> inverse_m_k(n, nullvector);
    /** Заполняем главную диагональ единицами,
        a k-ю строку -- элементами k+1 строки матрицы matrix*/
    for(int i = 0; i < n; i++){
        inverse_m_k[i][i] = 1;
        inverse_m_k[k][i] = matrix[k + 1][i];
    }
    return inverse_m_k;
}
/**Вспомогательный метод для умножения матриц размера n*n(левая) и n*n(правая)*/
std::vector<std::vector<float>> matrixProduct(
                                const std::vector<std::vector<float>> &left,
                                const std::vector<std::vector<float>> &right){
    /// Создаём матрицу product и заполняем её нулями (первоначально).
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

/** Приведение к канонической форме Фробениуса (КФФ) методом Данилевского.
    Если в ходе приведения КФФ выяснится, что случай нерелегулярный,
    метод завершится с результатом false*/
bool danilevskijMethod(std::vector<std::vector<float>> &matrix){
    bool result = true;
    /** Последовательно вычисляем матрицы M_k, INVERSE(M_k) и A_(n-1-k)
        где A_(n-1-k) ::= INVERSE(M_k) * A_(n-1-{k+1}) * M_k; A_0 = matrix.
        Примечание: т.к. индексы строк и столбцов сдвинуты, то мы ищем матрицы
        от M_(n-2) до M_0*/
    for(int k = n-2; k >= 0; k--){
        /** Если очередной ведущий элемент меньше epsilon, то мы считаем
            его нулём, а случай метода Данилевского -- нерегулярным.
            Выходим из метода, возвращая false*/
        if(abs(matrix[k+1][k]) < epsilon){
            std::cout << "\nUNREGULAR CASE!!!\n";
            result = false;
            break;
        }
        /// Иначе имеем (по крайней мере, на этом шаге) регулярный случай.
        else {
            /// Вычисляем M_k, INVERSE(M_k) для данного шага
            std::vector<std::vector<float>> m_k = computeM_k(matrix, k);
            std::vector<std::vector<float>> inverse_m_k =
                                                computeInverseM_k(matrix, k);
            /// Выводим M_k в консоль
             std::cout << "\n----------------------------------------\n";
             std::cout << "Matrix M_" << k+1 <<":\n";
             printMatrix(m_k);
            /// Вычисляем новую матрицу по формуле выше
            matrix = matrixProduct(inverse_m_k, matrixProduct(matrix, m_k));
        }
    }
    return result;
}
int main()
{
    bool success = true;
    float tr = 0;
    /** Цикл будет повторяться, пока мы не получим регулярный случай метода
        Данилевского.
    */
    std::vector<std::vector<float>> matrix;
        /// создаём и выводим матрицу
        matrix = {{ -0.6666666666, 2, -0.6666666666},
                  { 2, -0.3333333333, 1.3333333333},
                  { -0.6666666666, 1.3333333333, 1}};
        /// cчитаем след исходной матрицы
        tr = trace(matrix);
        std::cout << "\n----------------------------------------\n";
        std::cout << "Original matrix:\n";
        printMatrix(matrix);
        success = danilevskijMethod(matrix);
    /** Этот код выполнится, только если метод Данилевского
        даст регулярный случай для текущей матрицы.*/
    /// Выведем каноническую форму Фробениуса, след исх. матрицы и коэфф. p_1
    std::cout << "\n----------------------------------------\n";
    std::cout << "Frobenius normal form:\n";
    printMatrix(matrix);
    std::cout << "\n----------------------------------------\n";
    std::cout << "Trace of Frobenius normal form: ";
    std::cout << setprecision(DEF_WIDTH) << tr<<"\n";
    std::cout<<"Coefficient p_1: "<<setprecision(DEF_WIDTH)<<matrix[0][0]<<"\n";
    return 0;
}
