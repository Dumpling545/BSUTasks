#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
int m = 12;
int n = 18;
const int DEF_WIDTH = 10;
void printMatrix(float ** matrix, int a = DEF_WIDTH){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << std::setw(a)  << matrix[i][j];
            cout << " ";
        }
        cout <<"\n\n";
    }
}
void printVector(float * vector, int a = DEF_WIDTH){
    for(int i = 0; i < n; i++){
        cout << std::setw(a) << vector[i];
        cout << '\n';
    }
}
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
float* backSubstitution(float ** matrix, float * vector){
    float * result = new float[n];
    float temp_sum = 0;
    for(int i = n - 1; i  >= 0; i--){
        temp_sum = 0;
        result[i] = vector[i];
        for(int j = i + 1; j < n; j++){
            result[i] -= matrix[i][j] * result[j];
        }
        result[i] /= matrix[i][i];
    }
    return result;
}
float relativeError(float * result){
    float max_delta = abs(result[0] - m);
    float temp;
    for(int i = 1; i < n; i++){
        temp = abs(result[i] - m - i);
        if(temp > max_delta) max_delta = temp;
    }
    return max_delta / (m + n - 1);
}
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
///создание матрицы, создание вектора происходит аналогично задаче 1(a,b)
float** createMatrix(){
    srand (time(NULL));
    float ** matrix = new float*[n];
    for(int i = 0; i < n; i++){
        matrix[i] = new float[n];
        for(int j = 0; j < n; j++){
            matrix[i][j] = rand()%201 - 100;
        }
    }
    return matrix;
}
///выбор ведущего элемента по столбцу
///помимо матрицы и вектора передаётся индекс столбца, в котором нужно
///выбрать ведущий элемент
int chooseLeadingElement(float ** matrix, float * vector, int index){
    int maxrow = index;
    float temp;
    ///идем по столбцу и ищем индекс максимального элемента
    for(int i = index + 1; i < n; i++){
        temp = matrix[i][index];
        if(temp > matrix[maxrow][index]) maxrow = i;
    }
    return maxrow;
}
///перемена местами fi-й i si-й строк расширенной матрицы
void swapLines(float ** matrix, float * vector, int fi, int si){
    if(fi != si){
        float temp = vector[fi];
        vector[fi] = vector[si];
        vector[si] = temp;
        for(int i = 0; i < n; i++){
            temp = matrix[fi][i];
            matrix[fi][i] = matrix[si][i];
            matrix[si][i] = temp;
        }
    }
}
///прямой ход метода Гаусса
/// булевый параметр определяет, как модфикацию метода использовать
/// true - c выбором ведущего
/// false (по умолчанию) - без
void forwardElimantion(float ** matrix, float * vector,
                       bool with_choosing_leading_element = false){
    float l;
    ///идём по строкам матрицы
    for(int a = 0; a < n - 1; a++){
        ///эта часть выполнится, если вызывается метод Гаусса с выбором ведущего
        if(with_choosing_leading_element){
            ///ищем индекс ведущего элемента в a-м столбце
            int le_index = chooseLeadingElement(matrix, vector, a);
            ///меняем местами a-ю строку и строку, содержащую ведущию элемент
            swapLines(matrix, vector, a, le_index);
        }
        ///далее в методе аналогично задаче 1(a,b)
        for(int b = a + 1; b < n; b++){
            l = matrix[b][a] / matrix[a][a];
            vector[b] -= l*vector[a];
            matrix[b][a] = 0;
            for(int c = a + 1; c < n; c++){
                matrix[b][c] -= l*matrix[a][c];
            }
        }
        if(a == 0){
            cout << "\n\n Matrix after first step of forward elimination:\n";
            printMatrix(matrix, 12);
        }
    }
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
    ///МЕТОД ГАУССА БЕЗ ВЫБОРА ВЕДУЩЕГО
    ///создание матрицы и столбца свободных членов
    ///копирование данных для решения методом с выбором ведущего
    ///вывод входных данных
    cout << "Input:\n\n Matrix:\n";
    float ** matrix = createMatrix();
    float ** matrix_le = copyMatrix(matrix);
    printMatrix(matrix, 4);
    cout << "\n\n Vector:\n";
    float * vector = createVector(matrix);
    float * vector_le = copyVector(vector);
    printVector(vector, 6);
    ///метод Гаусса: прямой ход
    forwardElimantion(matrix, vector);
    ///метод Гаусса:обратный ход
    float * result = backSubstitution(matrix, vector);
    ///вывод результата
    cout << "\n\n\nResult:\n";
    printVector(result);
    ///вывод относительной погрешности
    cout << "\n\n\nRelative Error: "<<setprecision(DEF_WIDTH) << relativeError(result);
    ///МЕТОД ГАУССА БЕЗ ВЫБОРА ВЕДУЩЕГО
    ///аналогично предыдущему, в функции forwardElimantion последним параметром добавляем true
    cout << "\n\n...................................................................................................\n";
    cout << "WITH CHOOSING LEADING ELEMENT:\n\n";
    forwardElimantion(matrix_le, vector_le, true);
    float * result_le = backSubstitution(matrix_le, vector_le);
    cout << "\n\n\nResult:\n";
    printVector(result_le);
    cout << "\n\n\nRelative Error: "<<setprecision(DEF_WIDTH) << relativeError(result_le);
    return 0;
}
