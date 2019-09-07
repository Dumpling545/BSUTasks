#include "practice4.h"
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

int **fPrintMatrix(ofstream& fout, int ** matrix, int n, int m){
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

void fillMatrixUniqueNumbers(int **matrix, int n, int m){
    bool isUsed[n*m];
    srand(time(NULL));
    int counter = 0;
    int randValue;
    for(int k = 0; k < n*m; k++){
        isUsed[k] = false;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            randValue = rand() % (n*m);
            while(isUsed[randValue]){
                randValue = rand() % (n*m);
            }
            matrix[i][j] = randValue;
            isUsed[randValue] = true;
        }
    }
}

int ** fCreateMatrix(ifstream& fin, int n, int m){
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

int countUniqueMatrix(int **matrix, int n, int m){
    int counterRepeats= 0;
    for(int i = 0; i < n*m; i++){
        for(int j = i+1; j < n*m; j++){
            if(matrix[i/m][i%m] == matrix[j/m][j%m]){
                counterRepeats++;
                break;
            }
        }
    }
    return n*m - counterRepeats;
}

int countSignChangesMatrix(int **matrix, int n, int m){
    int changes = 0;
    for(int i = 0; i < n*m-1; i++){
        if(matrix[i/m][i%m] * matrix[(i+1)/m][(i+1)%m] < 0){
            changes++;
        }
    }
    return changes;
}

int countColumnPairsMatrix(int ** matrix, int n, int m){
    int counter = 0;
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < m; j++){
            if(matrix[i][j] == matrix[i+1][j]){
                counter++;
            }
        }
    }
    return counter;
}

int countRowPairsMatrix(int ** matrix, int n, int m){
    int counter = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m-1; j++){
            if(matrix[i][j] == matrix[i][j+1]){
                counter++;
            }
        }
    }
    return counter;
}

int sumRow(int ** matrix, int n, int index){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += matrix[index][i];
    }
    return sum;
}

int maxRowIndex(int ** matrix, int n){
    int resIndex = 0;
    int resValue = sumRow(matrix, n, 0);
    int temp = 0;
    for(int i = 1; i < n; i++){
        temp = sumRow(matrix, n, i) - matrix[i][i];
        if(temp > resValue){
            resValue = temp;
            resIndex = i;
        }
    }
    return resIndex;
}

int minRowIndex(int ** matrix, int n){
    int resIndex = 0;
    int resValue = sumRow(matrix, n, 0);
    int temp = 0;
    for(int i = 1; i < n; i++){
        temp = sumRow(matrix, n, i) - matrix[i][i];
        if(temp < resValue){
            resValue = temp;
            resIndex = i;
        }
    }
    return resIndex;
}
