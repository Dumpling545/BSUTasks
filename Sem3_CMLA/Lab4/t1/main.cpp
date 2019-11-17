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
/// вывод матрицы в консоль
void printMatrix(std::vector<std::vector<float>> matrix, int a = DEF_WIDTH){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << std::setw(a) << matrix[i][j];
        }
        cout <<'\n';
    }
}
/// вывод вектора в консоль
void printVector(std::vector<float> v, int a = DEF_WIDTH){
    for(int i = 0; i < n; i++){
        cout << std::setw(a) << v[i];
        cout << '\n';
    }
}
/** проверка на достижение требуемой точности
    (максимальная разность координат результатов двух итераций
     должна быть меньше epsilon)
*/
bool isPrecisionReached(std::vector<float> x,
                        std::vector<float> y){
    bool isReached = true;
    for(int i = 0; i < n && isReached; i++){
        isReached = (abs(x[i] - y[i]) < epsilon);
    }
    return isReached;
}

/// создание матрицы
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
/// создание вектора свободных значений по матрице (и вектору x решения)
std::vector<float> createVector(std::vector<std::vector<float>> matrix){
    std::vector<float> v(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            v[i]+= matrix[i][j]*(m + j);
        }
    }
    return v;
}
/// результат вычислений итеративным методом
struct IterativeResult{
    ///приближенное решение итеративным методом
    std::vector<float> result;
    /** номер итерации, на котором была достигнута заданная точность.
        -1, если превышено максимальное количество итераций*/
    int k;
};
/// решение СЛАУ методом Якоби
IterativeResult jakobiMethod(const std::vector<std::vector<float>> &matrix,
                                const std::vector<float> &f){
    /**задаём начальное значение x (до итераций),
       в данном случае заполняем нулями*/
    std::vector<float> result(n, 0);
    /**инициализируем вектор решения предыдущей итерации,
       первоначально заполняем так, чтобы разность с вектором result
       была больше заданной точности (иначе цикл не выполнится ни разу)*/
    std::vector<float> previous(n, epsilon*2);
    int iteration;
    for(iteration = 1;
        iteration <= k_max && !isPrecisionReached(result, previous);
        iteration++){
            /** вычисляем результат result для итерации iteration,
                в previous записываем результат итерации (iteration - 1)
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
    /** если точность достигнута, возвращаем номер итерации
        если точность не достигнута, возвращаем -1 */
    ir.k = (isPrecisionReached(result, previous)) ? iteration : -1;
    return ir;
}
///решение СЛАУ методом релаксации
IterativeResult sorMethod(const std::vector<std::vector<float>> &matrix,
                                const std::vector<float> &f, float omega){
    /**задаём начальное значение x (до итераций),
       в данном случае заполняем нулями*/
    std::vector<float> result(n, 0);
    /**инициализируем вектор решения предыдущей итерации,
       первоначально заполняем так, чтобы разность с вектором result
       была больше заданной точности (иначе цикл не выполнится ни разу)*/
    std::vector<float> previous(n, epsilon*2);
    int iteration;
    for(iteration = 1;
        iteration <= k_max && !isPrecisionReached(result, previous);
        iteration++){
            /** вычисляем результат result для итерации iteration,
                в previous записываем результат итерации (iteration - 1)
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
    /** если точность достигнута, возвращаем номер итерации
        если точность не достигнута, возвращаем -1 */
    ir.k = (isPrecisionReached(result, previous)) ? iteration : -1;
    return ir;
}
int main()
{
    ///создаем матрицу системы
    std::vector<std::vector<float>> matrix = createMatrix();
    /**создаём вектор f свободных членов по матрице
        и вектору решения x =(m,...,m+n-1)*/
    std::vector<float> f = createVector(matrix);
    ///выводим матрицу и вектор
    cout << "Input:\n\n Matrix:\n";
    printMatrix(matrix, 4);
    cout << "\n\n Vector:\n";
    printVector(f, 4);
    ///решаем СЛАУ методом Якоби
    cout << "\n\nJAKOBI METHOD: \n";
    IterativeResult jakobi = jakobiMethod(matrix, f);
    ///выводим результат и итерацию, на которой достигнута необходимая точность
    cout << "\n\nResult:\n";
    cout << "\n       Iteration: ";
    if(jakobi.k == -1){
        cout << "precision isn't reached on k_max iterations\n";
    } else {
        cout << jakobi.k<<"\n";
    }
    cout << "\n       Vector: \n";
    printVector(jakobi.result, 12);
    ///решаем СЛАУ методом релаксации для различных значений omega
    cout << "\nSOR METHOD: \n";
    for(float omega = 0.5; omega <= 1.5; omega+=0.5){
        cout << "\n\nWITH OMEGA="<<omega<<" \n\n";
        IterativeResult sor = sorMethod(matrix, f, omega);
        /** выводим результат и итерацию, на которой достигнута
        необходимая точность*/
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
