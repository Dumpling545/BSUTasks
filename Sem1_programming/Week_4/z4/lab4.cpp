#include "lab4.h"
using namespace std;
int oddTimesNumberInArrayByXor(int *ar, int n){
    int oddTimesNumber = ar[0];
    for(int i = 1; i < n; i++){
        oddTimesNumber = oddTimesNumber ^ ar[i];
    }
    return oddTimesNumber;
}

int oddTimesNumberInArrayBySort(int *ar, int n){
    selectionSort(ar, n);
    int currentNumber = ar[0];
    int currentCount = 0;
    for(int i = 0; i < n; i++){
        if(ar[i] == currentNumber){
            currentCount++;
        } else {
            if(currentCount % 2 == 1){
                return currentNumber;
                break;
            }
            currentNumber = ar[i];
            currentCount = 1;
        }
    }
}

int abs(int a){
    if(a >= 0){
        return a;
    } else {
        return -a;
    }
}
long long maxMultiplication(int *ar, int n){
    for(int i = 0; i < 2; i++){
        for(int j = i + 1; j < n; j++){
            if(ar[j] < ar[i]){
            int b = ar[i];
            ar[i] = ar[j];
            ar[j] = b;
            }
        }
    }
    for(int i = n-1; i >= n-3; i--){
        for(int j = i - 1; j >= 2; j--){
            if(ar[j] > ar[i]){
            int b = ar[i];
            ar[i] = ar[j];
            ar[j] = b;
            }
        }
    }

    long long maxMult1 = ar[0]*ar[1]*ar[n-1];
    long long maxMult2 = ar[n-1]*ar[n-2]*ar[n-3];
    if(maxMult1 > maxMult2){
        return maxMult1;
    } else {
        return maxMult2;
    }
}

int SortByMinimum(int *ar, int n){
    int minIndex = 0;
    for(int i = 0; i < n; i++){
        if(ar[i] < ar[minIndex]){
            minIndex = i;
        }
    }
    for(int i = 0; i < minIndex; i++){
        for(int j = i+1; j<minIndex; j++){
            if(ar[j] > ar[i]){
                int temp = ar[i];
                ar[i] = ar[j];
                ar[j] = temp;
            }
        }
    }
    for(int i = minIndex+1; i < n; i++){
        for(int j = i+1; j<n; j++){
            if(ar[j] < ar[i]){
                int temp = ar[i];
                ar[i] = ar[j];
                ar[j] = temp;
            }
        }
    }
    printArray(ar, n);
    return minIndex;
}

int* getSumPolynomial(int * alphas, int *betas, int n){
    int *ar= new int[n];
    for(int i = 0; i < n; i++){
        ar[i] = alphas[i] + betas[i];
    }
    return ar;
}

int* getMultiplicationPolynomial(int * alphas, int *betas, int n){
    int *ar = new int[2*n - 1];
    for(int i = 0; i < 2*n - 1; i++){
        int sum = 0;
        for(int j = 0; j <= i; j++){
            if(i - j < n && j < n){
                sum += alphas[i-j] * betas[j];
            }
        }
        ar[i] = sum;
    }
    return ar;
}

void nullArray(int *ar, int n){
    for(int i = 0; i < n; i++){
        ar[i] = 0;
    }
}

void reverseArray(int *ar, int n){
    for(int i = 0; i < n/2; i++){
        int temp = ar[i];
        ar[i] = ar[n - 1 - i];
        ar[n - 1 - i] = temp;
    }
}

void printPolynomial(int *ar, int n){
    bool notFirst = false;
    for(int i = 0; i < n-1; i++){
        if(ar[i]!= 0){
            if(ar[i] < 0){
                cout <<"  -  " << (-1) * ar[i] << " * x^" << n-i-1;
            } else {
                if(notFirst){
                    cout << "  +  ";
                }
                notFirst = true;
                cout << ar[i] << " * x^" << n-i-1;
            }
        }
    }
    if(ar[n-1] < 0){
        cout <<"  -  "<< (-1) * ar[n-1] <<endl;
    } else if(ar[n-1] > 0){
        cout <<"  +  "<< ar[n-1]<<endl;
    } else {
        cout <<endl;
    }
}

void enterNatural(int &n){
    cin >> n;
    while(n < 1){
        cout << "Incorrect natural number. Re-enter: " << endl;
        cin >> n;
    }
}

int gcd(int a, int b){
    if(a > b){
        gcd(a-b, b);
    } else if(a < b){
        gcd(b-a, a);
    } else {
        return a;
    }
}
int findStep(int * ar,int n){
    int d = gcd(ar[2] - ar[1], ar[1] - ar[0]);
    for(int i = 3; i < n; i++){
        d = gcd(d, ar[i] - ar[i-1]);
    }
    return d;
}
