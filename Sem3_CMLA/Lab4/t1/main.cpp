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
const int n = 12;
const int DEF_WIDTH = 32;
/// вывод матрицы в консоль
void printMatrix(std::vector<std::vector<float>> matrix, int a = DEF_WIDTH){
    for(int i = 0; i < N + 1; i++){
        for(int j = 0; j < N + 1; j++){
            cout << std::setw(a) << matrix[i][j];
        }
        cout <<'\n';
    }
}
/// вывод вектора в консоль
void printVector(std::vector<float> v, int a = DEF_WIDTH){
    for(int i = 0; i < N + 1; i++){
        cout << std::setw(a) << v[i];
        cout << '\n';
    }
}
/// создание матрицы
std::vector<std::vector<float>> createMatrix(){
    srand(time(null));
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
            v[i]+= matrix[i][j]*(j + 1);
        }
    }
    return v;
}


/** проверка на достижение требуемой точности
    (разность результатов двух итераций
     должна быть меньше epsilon)
*/
bool isPrecisionReached(std::vector<float> x,
                        std::vector<float> y,
                        float precision){
    bool isReached;
    for(int i = 0; i < n; i++){
        isReached = (abs(x[i] - y[i]) < epsilon);
    }
    return isReached;
}
int main()
{
    ///создаем матрицу системы
    std::vector<std::vector<float>> matrix = createMatrix();
    /**создаём вектор f свободных членов по матрице
        и вектору решения y =(1,...,N+1)*/
    std::vector<float> f = createVector(matrix);
    ///выводим матрицу и вектор
    cout << "Input:\n\n Matrix:\n";
    printMatrix(matrix, 4);
    cout << "\n\n Vector:\n";
    printVector(f, 4);
    /**создаём вектора alpha и beta, которыек будут
       заполнены методом прямой прогонки*/
    std::vector<float> alpha(N, 0), beta(N+1, 0);
    /// прямая прогонка
    forwardSweep(matrix, f, alpha, beta);
    /// вывод матрицы после прямой прогонки
    cout<<setprecision(DEF_WIDTH/4);
    printForwardSweepedMtrx(alpha, beta, 12);
    /// обратная прогонка
    std::vector<float> y = backSubstitution(alpha, beta);
    /// вывод результата
    cout << "\n\nResult:\n";
    printVector(y, 12);
    /// вывод ошибки
    cout << "\n\nRelative Error: "<<setprecision(DEF_WIDTH) << relativeError(y);
    return 0;
}
