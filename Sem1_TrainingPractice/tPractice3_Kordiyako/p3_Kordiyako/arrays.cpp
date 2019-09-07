#include "arrays.h"
using namespace std;
long long swapCounter = 0;
long long conditionCounter = 0;
long long getSwaps(){
    return swapCounter;
}
long long getCompares(){
    return conditionCounter;
}
void nullCounters(){
    swapCounter = 0;
    conditionCounter = 0;
}
void swapElements(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
    swapCounter++;
}

void  selectionSort(int *ar, int n){
    nullCounters();
    int minIndex;
    for(int i = 0; i < n; i++){
        minIndex = i;
        for(int j = i+1; j < n; j++){
            conditionCounter++;
            if(ar[j] < ar[minIndex]){
                minIndex = j;
            }
        }
        swapElements(ar[i], ar[minIndex]);
    }
}
void  insertionSort(int *ar, int n){
    nullCounters();
    for(int i = 1; i < n; i++){
        for(int j = i; j > 0; j--){
            conditionCounter++;
            if(ar[j] < ar[j-1]){
                swapElements(ar[j], ar[j-1]);
            } else {
                break;
            }
        }
    }
}
void  bubbleSort(int *ar, int n){
    nullCounters();
    for(int i = 0; i < n; i++){
        for(int j = n-1; j > i; j--){
            conditionCounter++;
            if(ar[j] < ar[j-1]){
                swapElements(ar[j], ar[j-1]);
            }
        }
    }
}

void  coctailSort(int *ar, int n){
    nullCounters();
    for(int i = 0; i < n/2; i++){
        for(int j = i; j < n -1 - i; j++){
            conditionCounter++;
            if(ar[j] > ar[j+1]){
                swapElements(ar[j], ar[j+1]);
            }
        }
        for(int k = n - 2 - i; k > i; k--){
            conditionCounter++;
            if(ar[k] < ar[k-1]){
                swapElements(ar[k-1], ar[k]);
            }
        }
    }
}

void  oddEvenSort(int *ar, int n){
    nullCounters();
    int counter = 1;
    while(counter != 0){
        counter = 0;
        for(int i = 0; i < n-1; i+=2){
            conditionCounter++;
            if(ar[i] > ar[i + 1]){
                swapElements(ar[i+1], ar[i]);
                counter++;
            }
        }
        for(int j = 1; j < n-1; j+=2){
            conditionCounter++;
            if(ar[j] > ar[j + 1]){
                swapElements(ar[j+1], ar[j]);
                counter++;
            }
        }
    }
}

int* generateArray(int n){
    int *ar = new int[n];
    for(int i = 0; i < n; i++){
        ar[i] =rand()%10000;
    }
    return ar;
}

void printArray(int *ar, int n){
    for(int i = 0; i < n; i++){
        cout<<ar[i]<<" ";
    }
    cout << endl;
}
int* enterArray(int n){
    cout << "Enter array: " <<endl;
    int *ar = new int[n];
    for(int i = 0; i < n; i++){
        cin >> ar[i];
    }
    return ar;
}
void copyArray(int *arFrom, int *arTo, int n){
    for(int i = 0; i < n; i++){
        arTo[i] = arFrom[i];
    }
}
void reverseArray(int *ar, int n){
    for(int i = 0; i < n/2; i++){
        int temp = ar[i];
        ar[i] = ar[n-1-i];
        ar[n-1-i] = temp;
    }
}
