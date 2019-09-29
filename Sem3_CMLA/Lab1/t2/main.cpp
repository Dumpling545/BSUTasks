#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;

int m = 12;
int n = 18;

void printElement(float element, int a = 9){
    stringstream ss;
    int d = a /2;
    ss.precision(d);
    ss << element;
    string s = ss.str();
    for (int i = 0; i < a - s.length(); i++){
        cout << ' ';
    }
    cout << s;
}
void printMatrix(float ** matrix, int a = 0){
    cout << std::fixed;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printElement(matrix[i][j], a);
        }
        cout <<'\n';
    }
}
void printVector(float * vector, int a = 0){
    cout << std::fixed;
    for(int i = 0; i < n; i++){
        printElement(vector[i], a);
        cout << '\n';
    }
}

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
int chooseLeadingElement(float ** matrix, float * vector, int index){
    int maxrow = index;
    float temp;
    for(int i = index + 1; i < n; i++){
        temp = matrix[i][index];
        if(temp > matrix[maxrow][index]) maxrow = i;
    }
    return maxrow;
}
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
void forwardElimantion(float ** matrix, float * vector,
                       bool with_choosing_leading_element = false){
    float l;
    for(int a = 0; a < n - 1; a++){
        if(with_choosing_leading_element){
            int le_index = chooseLeadingElement(matrix, vector, a);
            swapLines(matrix, vector, a, le_index);
        }
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
            printMatrix(matrix, 10);
        }
    }
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
float * copyVector(float * vector){
    float * copy = new float[n];
    for(int i = 0; i < n; i++){
        copy[i] = vector[i];
    }
    return copy;
}
int main()
{
    cout << "Input:\n\n Matrix:\n";
    float ** matrix = createMatrix();
    float ** matrix_le = copyMatrix(matrix);
    printMatrix(matrix, 8);
    cout << "\n\n Vector:\n";
    float * vector = createVector(matrix);
    float * vector_le = copyVector(vector);
    printVector(vector, 12);

    forwardElimantion(matrix, vector);
    float * result = backSubstitution(matrix, vector);

    cout << "\n\nResult:\n";
    printVector(result, 32);
    cout << "\n\nRelative Error: "<<setprecision(16) << relativeError(result);
    cout << "\n...................................................................................................\n";
    cout << "WITH CHOOSING LEADING ELEMENT:\n\n";
    forwardElimantion(matrix_le, vector_le, true);
    float * result_le = backSubstitution(matrix_le, vector_le);
    cout << "\n\nResult:\n";
    printVector(result_le, 32);
    cout << "\n\nRelative Error: "<<setprecision(16) << relativeError(result_le);
    return 0;
}
