#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
/// число точек
int n = 5;
/** размер матрицы для метода Гаусса:
    метод Гаусса проводится относительно тех
    неизвестных, которые были введены в доказательстве
    теоремы 12 (m_i, A_i, B_i)
*/
int s = 3*n - 2;

/** создание матрицы для метода Гаусса, первые n столбцов соответствуют
    переменным m_0, m_1, ... , m_(n-1),
    затем n-1 столбцов для переменных A_0, A_1, ..., A_(n-2)
    и n-1 столбцов для переменных B_0, B_1, ... B_(n-2)
    [обозначения теоремы 12, n -- число точек]
*/
float** createMatrix(float * x, float * f){
    float ** matrix = new float*[s];
    /// проинициализируем матрицу нулями
    for(int i = 0; i < s; i++){
        matrix[i] = new float[s];
        for(int j = 0; j < s; j++){
            matrix[i][j] = 0;
        }
    }
    /** первые 2*n - 2 строк будут соответствовать
        условиям совпадения значений в точках интерполяции
        c значениями исходной функции
    */
    int m_0 = 0;
    int A_0 = n;
    int B_0 = 2*n - 1;
    for(int i = 0; i < n - 1; i++){
        /// <0.5*x[i]*x[i]> * m_i + x[i] * A_i + B_i = f[i]
        matrix[2*i][m_0 + i] = 0.5*x[i]*x[i];
        matrix[2*i][A_0 + i] = x[i];
        matrix[2*i][B_0 + i] = 1;
        /** <1/6 * (3*x[i+1]*x[i+1] - {x[i+1] - x[i]}^2)> * m_i +
            <1/6 * {x[i+1] - x[i]}^2> * m_(i+1) +
            x[i+1] * A_i + B_i = f[i + 1]
        */
        float dx2 = x[i+1] - x[i];
        dx2*=dx2;
        matrix[2*i + 1][m_0 + i] = (3*x[i+1]*x[i+1] - dx2) / 6.0;
        matrix[2*i + 1][m_0 + i + 1] = dx2 / 6.0;
        matrix[2*i + 1][A_0 + i] = x[i+1];
        matrix[2*i + 1][B_0 + i] = 1;
    }
    /** следующие n - 2 строк -- условия совпадения
        первых производных в граничных точках:
        <0.5*(x[i] + x[i+1])> * m_(i+1) +
        <-0.5*(x[i] + x[i+1])> * m_i + A_(i+1) - A_i = 0
    */
    int offset = 2*n - 2;
    for(int i = 0; i < n - 2; i++){
        float k = 0.5*(x[i] + x[i+1]);
        matrix[offset + i][m_0 + i + 1] = k;
        matrix[offset + i][m_0 + i] = -k;
        matrix[offset + i][A_0 + i + 1] = 1;
        matrix[offset + i][A_0 + i] = -1;
    }
    /** последние две строки -- какие вторые
        производные будут иметь точки x_0 и x_n
        соответственно: фактически задание m_0 и m_(n-1) */
    matrix[3*n - 4][m_0] = 1;
    matrix[3*n - 3][m_0 + n - 1] = 1;
    return matrix;
}

/// заполнение столбца свободнцых членов для метода Гаусса
float* createVector(float * f,
                    float secondDerivativeInFirstPoint,
                    float secondDerivativeInLastPoint){
    /** первые 2*n - 2 строк будут соответствовать
        условиям совпадения значений в точках интерполяции
        c значениями исходной функции:
        свободные члены в них будут равны соответствующим значениям
        исходной функции в точках интерполирования
    */
    float * vector = new float[s];
    vector[0] = f[0];
    vector[2*n - 3] = f[n - 1];
    for(int i = 1; i < n - 1; i++){
        vector[2*i - 1] = f[i];
        vector[2*i] = f[i];
    }
    /** следующие n - 2 строк -- условия совпадения
        первых производных в граничных точках:
        свободные члено равны 0
    */
    for(int i = 2*n - 2; i < 3*n - 4; i++){
        vector[i] = 0;
    }
    /** последние две строки -- какие вторые
        производные будут иметь точки x_0 и x_n
        соответственно:
        свободные члены передаются в метод */
    vector[3*n - 4] = secondDerivativeInFirstPoint;
    vector[3*n - 3] = secondDerivativeInLastPoint;
    return vector;
}
/// обратный ход метода Гаусса
float* backSubstitution(float ** matrix, float * vector){
    float * result = new float[s];
    float temp_sum = 0;
    for(int i = s - 1; i  >= 0; i--){
        temp_sum = 0;
        result[i] = vector[i];
        for(int j = i + 1; j < s; j++){
            result[i] -= matrix[i][j] * result[j];
        }
        result[i] /= matrix[i][i];
    }
    return result;
}
///выбор ведущего элемента по столбцу
///помимо матрицы и вектора передаётся индекс столбца, в котором нужно
///выбрать ведущий элемент
int chooseLeadingElement(float ** matrix, float * vector, int index){
    int maxrow = index;
    float temp;
    ///идем по столбцу и ищем индекс максимального элемента
    for(int i = index + 1; i < s; i++){
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
        for(int i = 0; i < s; i++){
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
    for(int a = 0; a < s - 1; a++){
        ///эта часть выполнится, если вызывается метод Гаусса с выбором ведущего
        if(with_choosing_leading_element){
            ///ищем индекс ведущего элемента в a-м столбце
            int le_index = chooseLeadingElement(matrix, vector, a);
            ///меняем местами a-ю строку и строку, содержащую ведущию элемент
            swapLines(matrix, vector, a, le_index);
        }
        ///далее в методе аналогично задаче 1(a,b)
        for(int b = a + 1; b < s; b++){
            l = matrix[b][a] / matrix[a][a];
            vector[b] -= l*vector[a];
            matrix[b][a] = 0;
            for(int c = a + 1; c < s; c++){
                matrix[b][c] -= l*matrix[a][c];
            }
        }
    }
}
/// вычисление значения сплайна в точке point
float computeSplineValue(float point, float * solution, float * x){
    /**ищем промежуток в который попадает точка point:
        после выполнения цикла:  x[i-1] <= point <= x[i]
    */
    int i = 0;
    do{
        if(x[++i] > point) break;
    }while (i < n);
    /** вычисляем значение соответствующего многочлена в точке point:
        S(point) = {m_i - m_(i-1)} / (6*{x[i] - x[i - 1]}) * {point - x[i - 1]}^3 +
                0.5* m_(i-1) * point^2 + A_(i-1)* point + B_(i-1)
    */
    int m_0 = 0;
    int A_0 = n;
    int B_0 = 2*n - 1;
    float S = (solution[m_0 + i] - solution[m_0 + i - 1]) /
                (6.0*(x[i] - x[i - 1]));
    float delta3 = point - x[i - 1];
    delta3 *= (delta3*delta3);
    S*= delta3;
    S += 0.5 * solution[m_0 + i - 1] * point * point;
    S += solution[A_0 + i - 1] * point;
    S += solution[B_0 + i - 1];
    return S;
}
int main()
{
    ///постоить сплайн по таблице:
    ///(алгоритм корректно работает только при строгом возрастании в массиве х)
    float * x = new float[n]{0, 1, 2, 3, 4};
    float * f = new float[n]{0, 0.5, 0.86603, 1, 0.86603};
    /// дополнительные условия: значения второй производной в первой и последней точке
    float secondDerivativeInFirstPoint = 0;
    float secondDerivativeInLastPoint = 0;
    ///нужно вычилить значение сплайна в точке:
    float point = 1.5;
    /** создаём  матрицу matrix
        и столбец свободных членов vector
        для метода Гаусса
        более подробные комментарии в соответствующих методах
    */
    float ** matrix = createMatrix(x, f);
    float * vector = createVector(f,secondDerivativeInFirstPoint, secondDerivativeInLastPoint);
    /// прямой ход метода Гаусса
    forwardElimantion(matrix, vector, true);
    /// обратный ход метода Гаусса
    float * solution = backSubstitution(matrix, vector);
    /// вычисление значения сплайна по результатам метода Гаусса
    cout << "Spline value at x = "<<point<<":\n";
    cout <<computeSplineValue(point, solution, x);
    return 0;
}
