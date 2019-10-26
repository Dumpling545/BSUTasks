#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const float k = 1;
const int m = 12;
const int N = 10;
const int DEF_WIDTH = 32;
///вывод матрицы после пр€мой прогонки в консоль
void printForwardSweepedMtrx(std::vector<float> alpha,
                             std::vector<float> beta,
                             int a = DEF_WIDTH){
    for(int i = 0; i < N + 1; i++){
        for(int j = 0; j < N + 2; j++){
            if(j == N+1){
                cout<< std::setw(3)<<'|';
                cout<< std::setw(a)<<beta[i];
            } else if(j == i){
                cout<< std::setw(a)<<1;
            } else if(j == i+1){
                cout<< std::setw(a)<< -alpha[i];
            } else {
                cout << std::setw(a)<< 0;
            }
        }
        cout <<'\n';
    }
}
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
    std::vector<float> nullvector(N+1, 0);
    std::vector<std::vector<float>> matrix(N+1, nullvector);
    /// задаЄм первую строку
    matrix[0][0] = m;
    matrix[0][1] = m - 1;
    /// задаЄм последнюю строку
    matrix[N][N-1] = -k;
    matrix[N][N] = m + k + N - 1;
    /// задаЄм остальные
    for(int i = 1; i < N; i++){
        matrix[i][i-1] = -k;
        matrix[i][i] = m + k + i - 1;
        matrix[i][i+1] = m + i - 1;
    }
    return matrix;
}
/// создание вектора свободных значений по матрице (и вектору x решени€)
std::vector<float> createVector(std::vector<std::vector<float>> matrix){
    std::vector<float> v(N+1, 0);
    for(int i = 0; i < N + 1; i++){
        for(int j = 0; j < N + 1; j++){
            v[i]+= matrix[i][j]*(j + 1);
        }
    }
    return v;
}
/**пр€ма€ прогонка
   преобразуем систему от трЄхдиагональной к двухдиагональной следующего вида:
    1   -alpha_0     0     ...   0       0     |  beta_0
    0       1    -alpha_1  ...   0       0     |  beta_1
    ......................................................
    0       0        0     ...   1   -alpha_N-1|  beta_N-1
    0       0        0     ...   0       1     |  beta_N
*/
void forwardSweep(std::vector<std::vector<float>> matrix, std::vector<float> f,
                  std::vector<float>& alpha, std::vector<float>& beta){
    /// считаем коэффициенты alpha_0 и beta_0
    float b = -matrix[0][1];
    float c = matrix[0][0];
    alpha[0] = b / c;
    beta[0] = f[0] / c;
    float a;
    /// считаем коэффициенты alpha_1, ..., alpha_N-1 и beta_1, ..., beta_N-1
    for(int i = 1; i < N; i++){
        a = -matrix[i][i-1];
        c = matrix[i][i];
        b = -matrix[i][i+1];
        alpha[i] = b /(c - a*alpha[i-1]);
        beta[i] = (f[i] + a*beta[i-1])/(c - a*alpha[i-1]);
    }
    /// считаем коэффициент beta_N
    a = -matrix[N][N-1];
    c = matrix[N][N];
    beta[N] = (f[N] + a*beta[N-1])/(c - a*alpha[N-1]);
}
/**обратна€ прогонка
   решаем двухдиагональную систему*/
std::vector<float>  backSubstitution(std::vector<float> alpha,
                                     std::vector<float> beta){
    std::vector<float> y(N+1, 0);
    /** последн€€ координата y_N вектора решений равна последней
    координате beta_N вектора beta из пр€мой прогонки*/
    y[N] = beta[N];
    /// вычисл€ем остальные координаты вектора решений
    for(int i = N-1; i >=0; i--){
        y[i] = alpha[i]*y[i+1] + beta[i];
    }
    return y;
}
///вычисление относительной ошибки при помощи максимум-нормы
float relativeError(std::vector<float> result){
    float max_delta = abs(result[0] - 1);
    float temp;
    for(int i = 1; i < N + 1; i++){
        temp = abs(result[i] - i - 1);
        if(temp > max_delta) max_delta = temp;
    }
    return max_delta / (N + 1);
}
int main()
{
    ///создаем матрицу системы
    std::vector<std::vector<float>> matrix = createMatrix();
    /**создаЄм вектор f свободных членов по матрице
        и вектору решени€ y =(1,...,N+1)*/
    std::vector<float> f = createVector(matrix);
    ///выводим матрицу и вектор
    cout << "Input:\n\n Matrix:\n";
    printMatrix(matrix, 4);
    cout << "\n\n Vector:\n";
    printVector(f, 4);
    /**создаЄм вектора alpha и beta, которыек будут
       заполнены методом пр€мой прогонки*/
    std::vector<float> alpha(N, 0), beta(N+1, 0);
    /// пр€ма€ прогонка
    forwardSweep(matrix, f, alpha, beta);
    /// вывод матрицы после пр€мой прогонки
    cout<<setprecision(DEF_WIDTH/4);
    printForwardSweepedMtrx(alpha, beta, 12);
    /// обратна€ прогонка
    std::vector<float> y = backSubstitution(alpha, beta);
    /// вывод результата
    cout << "\n\nResult:\n";
    printVector(y, 12);
    /// вывод ошибки
    cout << "\n\nRelative Error: "<<setprecision(DEF_WIDTH) << relativeError(y);
    return 0;
}
