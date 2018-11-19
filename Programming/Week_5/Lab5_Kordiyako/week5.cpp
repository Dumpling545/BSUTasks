#include <queue>
#include "arrays.h"
#include "week5.h"
int sumRow(int ** matrix, int n, int index){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += matrix[index][i];
    }
    return sum;
}
int sumColumn(int ** matrix, int n, int index){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += matrix[i][index];
    }
    return sum;
}
bool isMagic(int ** matrix, int n){
    //compare rows and columns by sum
    int sum = sumRow(matrix, n, 0);
    for(int i = 0; i < n; i++){
        int cSum = sumColumn(matrix, n, i);
        int cRow = sumRow(matrix, n, i);
        if(cSum != cRow || cRow != sum){
            return false;
        }
    }

    //unique elements check
    int* ar = new int[n*n];
    //conversion into one-dimensional array
    for(int i = 0; i < n*n; i++){
        ar[i] = matrix[i / n][i % n];
    }
    //sort
    selectionSort(ar, n*n);
    //search for equal
    for(int i = 0; i < n*n-1; i++){
        if(ar[i] == ar[i+1]){
            return false;
        }
    }
    return true;
}

int enterMatrixWithTwoes(int **matrix, int n){
    int value = 2;
    for(int i = 0; i < n/2+1; i++){
        for(int j = i; j < n - i;j++){
            matrix[i][j] = value;
            value+=2;
        }
        for(int j = i+1; j < n - i; j++){
            matrix[j][n-1-i] = value;
            value+=2;
        }
        for(int j = n-i-2; j >= i; j--){
            matrix[n-1-i][j] = value;
            value+=2;
        }
        for(int j = n - i - 2; j >= i + 1; j--){
            matrix[j][i] = value;
            value+=2;
        }
    }
    return value;
}
void printMatrix(int **matrix, int n, int maxValue){
    int symbols = 0;
    while(maxValue > 0){
        maxValue/=10;
        symbols++;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout <<setw(symbols)<< matrix[i][j] << " ";
        }
        cout <<endl;
    }
}
int** createMatrix(int n, int m){
    int **matrix = new int*[n];
    for(int i =0; i<n;i++){
        matrix[i] = new int[m];
    }
    return matrix;
}
int** createMatrix(int n){
    return createMatrix(n, n);
}

int* BinaryEnter(int *ar, int n, int value, int _start, int _ending){

    int start = _start >= 0 ? _start : 0;
    int ending = _ending > 0 ? _ending : n-1;
    do{
        int temp = (ending + start)/2;
        if(ar[temp] >= value){
            ending = temp;
        }  else{
            start = temp + 1;
        }
    }while(ending - start > 0);
    return &ar[ending];
}

void  insertionSortWithBSWithBS(int *ar, int n){
    for(int i = 1; i < n; i++){
        int *place = BinaryEnter(ar, n, ar[i], 0, i);
        int temp = ar[i];
        for(int *ptr = &ar[i]; ptr > place; ptr--){
            *ptr = *(ptr - 1);
        }
        *place = temp;
    }
}
int*  normalizeSet(int *unnormalizedSet, int &n){
    bool *uniques = new bool[n];
    for(int i = 0; i < n; i++){
        uniques[i] = true;
    }
    int newSize = n;
    insertionSortWithBSWithBS(unnormalizedSet, n);
    for(int i = 1; i < n; i++){
        if(unnormalizedSet[i] == unnormalizedSet[i-1]){
            uniques[i] = false;
            newSize--;
        }
    }
    int *temp = new int[newSize];
    int c = 0;
    for(int i = 0; i < n; i++){
        if(uniques[i]){
            temp[c] = unnormalizedSet[i];
            c++;
        }
    }
    unnormalizedSet = new int[newSize];
    for(int i = 0; i < newSize; i++){
        unnormalizedSet[i] = temp[i];
    }
    n = newSize;
    return unnormalizedSet;
}
int* isSubstring(int *baseString, int baseStringSize, int *predictingSubstring, int predictingSubstringSize){
    if(baseStringSize < predictingSubstringSize){
        return  0;
    }
    int subIndex = 0;
    int start = 0;
    for(int i = 0; i < baseStringSize; i++){
        if(baseString[i] == predictingSubstring[subIndex]){
            start = i;
            subIndex++;
        } else {
            subIndex = 0;
            if(baseString[i] == predictingSubstring[subIndex]){
                start = i;
                subIndex++;
            }
        }
        if(subIndex == predictingSubstringSize){
            return &baseString[start];
        }
    }
    return 0;
}

bool isSubset(int *baseSet, int baseSetSize, int *predictingSubset, int predictingSubsetSize){
    if(predictingSubsetSize > baseSetSize){
        return false;
    } else {
        int * newSet = normalizeSet(baseSet, baseSetSize);
        int *newSubset = normalizeSet(predictingSubset, predictingSubsetSize);
        int subIndex = 0;
        for(int i  = 0; i < baseSetSize; i++){
            if(newSet[i] == newSubset[subIndex]){
                subIndex++;
            }
        }
        return subIndex == predictingSubsetSize;
    }
}

bool CanGo(int fromValue, int toValue){
    return toValue < fromValue;
}
void fillMatrix(int**matrix, int n, int m, int value){
    for(int i = 0; i <n; i++){
        for(int j = 0; j <m;j++){
            matrix[i][j] = value;
        }
    }
}
int ** BFS(int**matrix, int n, int m, int x_start, int y_start, bool (*canGo)(int, int)){
    int **result = createMatrix(n, m);
    fillMatrix(result, n, m, -1);
    result[x_start][y_start] = 0;
    queue<int> xs;
    queue<int> ys;
    xs.push(x_start);
    ys.push(y_start);
    while(!xs.empty()){
        int x = xs.front();
        int y = ys.front();
        if(x > 0 && canGo(matrix[x][y], matrix[x-1][y]) && result[x-1][y] == -1){
            result[x-1][y] = result[x][y]+1;
            xs.push(x-1);
            ys.push(y);
        }
        if(x < n-1 && canGo(matrix[x][y], matrix[x+1][y]) && result[x+1][y] == -1){
            result[x+1][y] = result[x][y]+1;
            xs.push(x+1);
            ys.push(y);
        }
        if(y > 0 && canGo(matrix[x][y], matrix[x][y-1]) && result[x][y-1] == -1){
            result[x][y-1] = result[x][y]+1;
            xs.push(x);
            ys.push(y-1);
        }
        if(y < m-1 && canGo(matrix[x][y], matrix[x][y+1]) && result[x][y + 1] == -1){
            result[x][y+1] = result[x][y]+1;
            xs.push(x);
            ys.push(y+1);
        }
        xs.pop();
        ys.pop();
    }
    return result;
}
pair<int, int>  mostDistantElement(int**matrix, int n, int m, int x0, int y0){
    pair <int,int> mde;
    mde.first = 0;
    mde.second = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m;j++){
            if(matrix[i][j] > matrix[mde.first][mde.second]){
                mde.first = i;
                mde.second = j;
            }
        }
    }
    return mde;
}
bool** canReach(int**matrix, int n, int m, int x0, int y0){
    bool **can = new bool*[n];
    for(int i = 0; i < n; i++){
        can[i] = new bool[m];
        for(int j = 0; j < m;j++){
            can[i][j] = (matrix[i][j] >= 0);
        }
    }
    return can;
}
bool matchMatrix(int value){
    return (value >= 0);
}
void fillMatrixWithRandomValues(int **matrix, int n, int m, bool shouldPrint){
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
