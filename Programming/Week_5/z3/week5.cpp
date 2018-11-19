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
int** createMatrix(int n){
    int **matrix = new int*[n];
    for(int i =0; i<n;i++){
        matrix[i] = new int[n];
    }
    return matrix;
}
void enterNatural(int &n){
    cout << "Enter n:" << endl;
    cin >> n;
    while(n < 1){
        cout << "Incorrect natural number. Re-enter:" << endl;
        cin >> n;
    }
}
int* BinaryEnter(int *ar, int n, int value, int _start = 0, int _ending = 0){

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
int* enterArray(int n){
    cout << "Enter array: " <<endl;
    int *ar = new int[n];
    for(int i = 0; i < n; i++){
        cin >> ar[i];
    }
    return ar;
}
void enterNatural(int &n, string inputName){
    cout << "Enter "<<inputName <<": " << endl;
    cin >> n;
    while(n < 1){
        cout << "Incorrect natural number. Re-enter:" << endl;
        cin >> n;
    }
}
void printArray(int *ar, int n){
    for(int i = 0; i < n; i++){
        cout<<ar[i]<<" ";
    }
    cout << endl;
}
int* BinaryEnter(int *ar, int n, int value, int _start = 0, int _ending = 0){

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
int* enterArray(int n, string inputName){
    cout << "Enter array "<<inputName<<": " <<endl;
    int *ar = new int[n];
    for(int i = 0; i < n; i++){
        cin >> ar[i];
    }
    return ar;
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

