#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

float k = 0;/// int k = 1 для задачи 1b
int m = 12;
int n = 10;
const int DEF_WIDTH = 32;
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
/// созднание матрицы
std::vector<std::vector<float>> createMatrix(){
    srand (time(NULL));
    float temp_sum = 0;
    vector<std::vector<float>> matrix(n);
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
    matrix[0][0] += pow(10.0 , -k);
    return matrix;
}
/// создание вектора свободных значений по матрице (и вектору x решения)
std::vector<float> createVector(std::vector<std::vector<float>> matrix){
    std::vector<float> v(n, 0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            v[i]+= matrix[i][j]*(m + j);
        }
    }
    return v;
}
/// Метод разложения симметрической матрицы A в произведение L*D*t(L)
void ldltDecomposition(std::vector<std::vector<float>>& matrix){
    std::vector<float> t(n);
    ///Идём по строкам разлагаемой матрицы (кроме последней)
    for(int s = 0; s < n - 1; s++){
        ///Идём по всем строкам, следующим за s-й строкой
        for(int i = s + 1; i < n; i++){
            ///Временно сохраняем исходное значение эл-та (i,s)
            t[i] = matrix[i][s];
            ///В столбце под ведущим эл-том сохраняем L(i,s) -- элементы матрицы L
            matrix[i][s] /= matrix[s][s];
            /**Далее, из i-й строки, начиная со столбца, следующего за сохранённым L(i,s),
                вычитаем s-ю строку, умноженную на L(i,s)*/

            /**Т.к. матрица симметрична, мы  доходим лишь до диагонального элемента (i,i);
                по той же причине вместо вычитания (i,j) - (s,j)*L(i,s) мы используем
                (i,j) - (j,s)*L(i,s) {исходный (j,s) хранится в t[j]}*/
            for(int j = s + 1; j <= i; j++){
                matrix[i][j] -= t[j] * matrix[i][s];
            }
        }
    }
}
/** Метод решения уравнения вида L*X = B

    Иначе говоря метод решения матричного уравнения с
    нижнетреугольной матрицей
*/
std::vector<float> compute_LX_equals_B(std::vector<std::vector<float>> matrix,
                           std::vector<float> v){
    std::vector<float> result(n);
    /**Вычисляем на каждом шаге одну из координат вектора решений,
        алгоритм по сути является обратным ходом метода Гаусса (далее ОХМГ).

        Для L {нижнетреугольной} алгоритм начинает вычислять вектор решений с первой
        координаты и двигается по диагонали матрицы сверху вниз, используя при вычислении
        очередной координаты элементы, стоящие слева от диагональных
    */
    for(int i = 0; i  < n; i++){
        result[i] = v[i];
        for(int j = 0; j < i; j++){
            result[i] -= matrix[i][j] * result[j];
        }
    }
    return result;
}

/** Метод решения уравнения вида t(L)*X = B

    Иначе говоря метод решения матричного уравнения с
    транспонированием исходной нижнетреугольной матрицы
*/
std::vector<float> compute_tLX_equals_F(std::vector<std::vector<float>> matrix,
                           std::vector<float> v){
    std::vector<float> result(n);
    /**Вычисляем на каждом шаге одну из координат вектора решений,
        алгоритм - обратный ход метода Гаусса (с тем лишь отличием, что мы
        берём транспонированные элементы)
    */
    for(int i = n - 1; i  >= 0; i--){
        result[i] = v[i];
        for(int j = i + 1; j < n; j++){
            result[i] -= matrix[j][i] * result[j];
        }
    }
    return result;
}

/**Метод решения уравнения вида D*Y=C

    Иначе говоря метод решения матричного уравнения с
    диагональной матрицей*/
std::vector<float> compute_DX_equals_C(std::vector<std::vector<float>> matrix,
                                       std::vector<float> v){
    std::vector<float> result(n);
    for(int i = 0; i < n; i++){
        result[i] = v[i] / matrix[i][i];
    }
    return result;
}
///вычисление относительной ошибки при помощи максимум-нормы
float relativeError(std::vector<float> result){
    float max_delta = abs(result[0] - m);
    float temp;
    for(int i = 1; i < n; i++){
        temp = abs(result[i] - m - i);
        if(temp > max_delta) max_delta = temp;
    }
    return max_delta / (m + n - 1);
}
int main()
{
    ///создаем массив из двух матриц: для задачи 1.a и 1.b соотвественно
    std::vector<std::vector<float>> matrix_array[2];
    matrix_array[0] = createMatrix();
    matrix_array[1] = matrix_array[0];
    matrix_array[1][0][0]-=pow(10.0 , -k);
    k = 1;
    matrix_array[1][0][0]+=pow(10.0 , -k);
    for(int p = 0; p < 2; p++){
        cout << "\n\n...................................................................................................\n";
        cout << "WITH K="<<p<<":\n\n";
        ///создание и вывод входных данных
        cout << "Input:\n\n Matrix:\n";
        printMatrix(matrix_array[p]);
        cout << "\n\n Vector:\n";
        std::vector<float> v = createVector(matrix_array[p]);
        printVector(v);
        ///разложение LDt(L)
        ldltDecomposition(matrix_array[p]);
        cout << "\n\nLDt(L) decomposition:\n";
        printMatrix(matrix_array[p], 30);
        ///решение СЛАУ c использованием разложения
        /// шаг 1: решаем СЛАУ LY=b
        std::vector<float> y = compute_LX_equals_B(matrix_array[p], v);
        /// шаг 2: решаем СЛАУ DZ=Y
        std::vector<float> z = compute_DX_equals_C(matrix_array[p], y);
        /// шаг 3: решаем СЛАУ t(L)X=Z
        std::vector<float> result = compute_tLX_equals_F(matrix_array[p], z);
        ///вывод результата
        cout << "\n\nResult:\n";
        printVector(result);
        ///вывод ошибки
        cout << "\n\nRelative Error: "<<setprecision(DEF_WIDTH) << relativeError(result);
    }
    return 0;
}
