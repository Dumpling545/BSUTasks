#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;
/**
        Дана матрица размера m x n.
        Перестроить матрицу, переставляя в ней строки так,
        чтобы сумма элементов в строках полученной матрицы возрастала.
        Выполнил: Кордияко Ян

        Input                       Output
        ----------------------------------------------------
        3 4                         1 2 3 4
        9 8 7 6                     5 6 7 8
        1 2 3 4                     9 8 7 6
        5 6 7 8

*/
ofstream fout("output.txt");
ifstream fin("input.txt");
int sumRow(int ** matrix, int n, int index){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += matrix[index][i];
    }
    return sum;
}
void swapElements(int* &a, int* &b, int m){
    for(int i = 0; i< m; i++){
        int temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

void  selectionSort(int **matrix, int n, int m){
    int minIndex;
    for(int i = 0; i < n; i++){
        minIndex = i;
        for(int j = i+1; j < n; j++){

            if(sumRow(matrix, m, j)< sumRow(matrix, m, minIndex)){
                minIndex = j;
            }
        }
        swapElements(matrix[i], matrix[minIndex], m);
    }
}
int** createMatrix(int n, int m){
    int **matrix;
    if(n > 0 && m > 0){
        matrix = new int*[n];
        for(int i =0; i<n;i++){
            matrix[i] = new int[m];
        }
    }
    return matrix;
}

int maxAtMatrix(int ** matrix, int n, int m){
    int maxValue = matrix[0][0];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(maxValue < matrix[i][j]){
                maxValue = matrix[i][j];
            }
        }
    }
    return maxValue;
}

int minAtMatrix(int ** matrix, int n, int m){
    int minValue = matrix[0][0];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(minValue > matrix[i][j]){
                minValue = matrix[i][j];
            }
        }
    }
    return minValue;
}

int **fPrintMatrix( int ** matrix, int n, int m){
    fout << endl;
    int symbols = 0;
    int maxValue = max(abs(maxAtMatrix(matrix, n, m)), abs(minAtMatrix(matrix, n, m)));
    while(maxValue > 0){
        maxValue/=10;
        symbols++;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            fout <<setw(symbols)<< matrix[i][j] << " ";
        }
        fout <<endl;
    }
    fout << endl;
}
int ** fCreateMatrix(int n, int m){
    int** matrix = createMatrix(n, m);
    if(n > 0 && m > 0){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                fin >> matrix[i][j];
            }
        }
    }
    return matrix;
}
int main()
{
    int n, m;
    while(fin >> n >> m){
        int ** matrix = fCreateMatrix(n, m);
        selectionSort(matrix, n, m);
        fPrintMatrix(matrix, n, m);
    }
    return 0;
}
