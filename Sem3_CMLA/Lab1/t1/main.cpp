#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;

float k = 0;/// int k = 1 для задачи 1b
int m = 12;
int n = 14;
const int DEF_WIDTH = 32;
/// вывод матрицы в консоль
void printMatrix(float ** matrix, int a = DEF_WIDTH){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << std::setw(a) << matrix[i][j];
        }
        cout <<'\n';
    }
}
/// вывод вектора в консоль
void printVector(float * vector, int a = DEF_WIDTH){
    for(int i = 0; i < n; i++){
        cout << std::setw(a) << vector[i];
        cout << '\n';
    }
}
/// созднание матрицы
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
/// создание вектора свободных значений по матрице (и вектору x решения)
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
/// прямой ход метода Гаусса без выбора ведущего элемента
void forwardElimantion(float ** matrix, float * vector){
    float l;
    ///идём по строкам матрицы
    for(int a = 0; a < n - 1; a++){
        ///идём по всем строкам, следующим за a-й строкой
        for(int b = a + 1; b < n; b++){
            /// вычисляем коэффициент l для b-й строки
            l = matrix[b][a] / matrix[a][a];
            ///вычитаем a-ю строку расширенной матрицы,
            ///умноженную на коэффицент l, из b-й строки
            vector[b] -= l*vector[a];
            matrix[b][a] = 0;
            for(int c = a + 1; c < n; c++){
                matrix[b][c] -= l*matrix[a][c];
            }
        }
        ///вывод в консоль матрицы после первой итерации метода Гаусса
        if(a == 0){
            cout << "\n\n Matrix after first step of forward elimination:\n";
            printMatrix(matrix);
        }
    }
}
///обратный ход метода Гаусса
float* backSubstitution(float ** matrix, float * vector){
    float * result = new float[n];
    ///идём по строкам преобразованной матрицы в обратном направлении,
    ///вычисляя на каждом шаге одну из координат вектора решений
    for(int i = n - 1; i  >= 0; i--){
        result[i] = vector[i];
        for(int j = i + 1; j < n; j++){
            result[i] -= matrix[i][j] * result[j];
        }
        result[i] /= matrix[i][i];
    }
    return result;
}
///вычисление относительной ошибки метода Гаусса при помощи максимум-нормы
float relativeError(float * result){
    float max_delta = abs(result[0] - m);
    float temp;
    for(int i = 1; i < n; i++){
        temp = abs(result[i] - m - i);
        if(temp > max_delta) max_delta = temp;
    }
    return max_delta / (m + n - 1);
}
///копирование матрицы
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
///копирование вектора
float * copyVector(float * vector){
    float * copy = new float[n];
    for(int i = 0; i < n; i++){
        copy[i] = vector[i];
    }
    return copy;
}
int main()
{
    ///создание и вывод входных данных
    cout << "Input:\n\n Matrix:\n";
    float ** matrix = createMatrix();
    float ** copy_matrix = copyMatrix(matrix);
    printMatrix(matrix, 4);
    cout << "\n\n Vector:\n";
    float * vector = createVector(matrix);
    printVector(vector,6);
    ///решение СЛАУ: прямой ход
    forwardElimantion(matrix, vector);
    ///решение СЛАУ: обратный ход
    float * result = backSubstitution(matrix, vector);
    ///вывод результата
    cout << "\n\nResult:\n";
    printVector(result);
    ///вывод ошибки
    cout << "\n\nRelative Error: "<<setprecision(DEF_WIDTH) << relativeError(result);
    ///повторяем аналогичные действия для k = 1
    cout << "\n\n...................................................................................................\n";
    cout << "WITH K=1:\n\n";
    ///изменяем скопированную матрицу так, чтобы она соответствовала k = 1
    copy_matrix[0][0]-=pow(10.0 , -k);
    k = 1;
    copy_matrix[0][0]+=pow(10.0 , -k);
    cout << "Input:\n\n Matrix:\n";
    printMatrix(copy_matrix);
    cout << "\n\n Vector:\n";
    ///строим вектор свободных членов для новой матрицы
    float * vector1 = createVector(copy_matrix);
    printVector(vector1,6);
    forwardElimantion(copy_matrix, vector1);
    float * result1 = backSubstitution(copy_matrix, vector1);
    cout << "\n\nResult:\n";
    printVector(result1);
    cout << "\n\nRelative Error: "<<setprecision(DEF_WIDTH) << relativeError(result1);
    return 0;
}
