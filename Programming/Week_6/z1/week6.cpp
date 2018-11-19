#include "week6.h"
double addition(double a, double b){
    return a+b;
}
double multiplication(double a, double b){
    return a*b;
}
double subtraction(double a, double b){
    return a-b;
}
double division(double a, double b){
    return a/b;
}
void printOperation(double (*operation)(double, double)){
    double a,b;
    cout << "Enter a,b" << endl;
    cin >> a >> b;
    cout << "Result: " << operation(a,b) << endl;
}
int* findPrimes(int *a, int n, int &newIndex){
    int *result = new int[n];
    int index = 0;
    bool isPrime = true;
    for(int i = 0; i < n; i++){
            isPrime = true;
        for(int j = 2; j*j <= a[i]; j++){
            if(a[i] % j == 0){
                isPrime = false;
                break;
            }
        }
        if(isPrime){
            result[index] = a[i];
            index++;
        }
    }
    int * resultResized = new int[index];
    for(int i = 0; i < index; i++){
        resultResized[i] = result[i];
    }
    delete [] result;
    newIndex = index;
    return resultResized;
}
int * findEvens(int *a, int n, int &newIndex){
    int *result = new int[n];
    int index = 0;
    for(int i = 0; i < n; i++){
        if(a[i] % 2 == 0){
            result[index] = a[i];
            index++;
        }
    }
    int * resultResized = new int[index];
    for(int i = 0; i < index; i++){
        resultResized[i] = result[i];
    }
    delete [] result;
    newIndex = index;
    return resultResized;
}
int * findMultiplesOfThree(int *a, int n, int &newIndex){
    int *result = new int[n];
    int index = 0;
    for(int i = 0; i < n; i++){
        if(a[i] % 3 == 0){
            result[index] = a[i];
            index++;
        }
    }
    int * resultResized = new int[index];
    for(int i = 0; i < index; i++){
        resultResized[i] = result[i];
    }
    delete [] result;
    newIndex = index;
    return resultResized;
}
void printOperation(int*ar, int n, int* (*operation)(int*, int, int&)){
    int temp = 0;
    int *res=operation(ar,n,temp);
    printArray(res, temp);
    delete [] res;
}

void printMatrix(int** matrix, int n, int m, int maxValue){
    int symbols = 0;
    while(maxValue > 0){
        maxValue/=10;
        symbols++;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout <<setw(symbols)<< matrix[i][j] << " ";
        }
        cout <<endl;
    }
}
void fillMatrixWithRandomValues(int **matrix, int n, int m, bool shouldPrint){
    srand(time(NULL));
    if(shouldPrint){
        cout << "Matrix: " <<endl;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            matrix[i][j] = rand()%100;
            if(shouldPrint){
                cout << setw(2) << matrix[i][j] << " ";
            }
        }
        if(shouldPrint){
            cout <<endl;
        }
    }
}
int ** createMatrixWithRandomValues(int n, int m, bool shouldPrint){
    int **matrix = new int*[n];
    for(int i = 0; i < n; i++){
        matrix[i]= new int[m];
    }
    fillMatrixWithRandomValues(matrix,n,m,shouldPrint);
    return matrix;
}
void insertRow(int **& matrix, int &n, int m, int *newRow, int position){
        n++;
        int **result = new int*[n];
        for(int i = 0; i < n; i++){
            result[i] = new int[m];
        }
        for(int i = 0; i < position; i++){
            result[i] = matrix[i];
        }
        result[position] = newRow;
        for(int i = position + 1; i < n; i++){
            result[i] = matrix[i-1];
        }
        delete [] matrix;
        matrix = new int*[n];
        for(int i = 0; i < n; i++){
            matrix[i] = result[i];
        }
        delete [] result;
}
void insertColumn(int **& matrix, int n, int &m, int *newColumn, int position){
        int **result = new int*[n];
        m++;
        for(int i = 0; i < n; i++){
            result[i] = new int[m];
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < position; j++){
                result[i][j] = matrix[i][j];
            }
        }
        for(int i = 0; i < n; i++){
            result[i][position] = newColumn[i];
        }
        for(int i = 0; i < n; i++){
            for(int j = position + 1; j < m; j++){
                result[i][j] = matrix[i][j-1];
            }
        }
        delete [] matrix;
        matrix = new int*[n];
        for(int i = 0; i < n; i++){
            matrix[i] = result[i];
        }
        delete [] result;
}
void deleteRow(int **& matrix, int &n, int m, int position){
    n--;
    int **result = new int*[n];
    for(int i = 0; i < n; i++){
        result[i] = new int[m];
    }
    for(int i = 0; i < position; i++){
        result[i] = matrix[i];
    }
    for(int i = position; i < n; i++){
        result[i] = matrix[i+1];
    }
    delete [] matrix;
    matrix = new int*[n];
    for(int i = 0; i < n; i++){
        matrix[i] = result[i];
    }
    delete [] result;
}
void deleteColumn(int **& matrix, int n, int &m,  int position){
    int **result = new int*[n];
    m--;
    for(int i = 0; i < n; i++){
        result[i] = new int[m];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < position; j++){
            result[i][j] = matrix[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = position; j < m; j++){
            result[i][j] = matrix[i][j+1];
        }
    }
    delete [] matrix;
    matrix = new int*[n];
    for(int i = 0; i < n; i++){
        matrix[i] = result[i];
    }
    delete [] result;
}
