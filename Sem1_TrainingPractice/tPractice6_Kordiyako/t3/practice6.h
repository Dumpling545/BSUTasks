#pragma once
#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

template <typename T>
int maxElemIndexRecursion(const T* ar, const int n, int startIndex, int maxIndex){
    maxIndex = ar[maxIndex] >= ar[startIndex] ? maxIndex : startIndex;
    if(startIndex + 1 < n){
        return maxElemIndexRecursion(ar, n, startIndex+1, maxIndex);
    } else {
        return maxIndex;
    }
}
template <typename T>
int maxElemIndex(const T* ar, const int n){
    if(n > 1) {
        return maxElemIndexRecursion(ar, n, 1, 0);
    } else if(n == 1){
        return ar[0];
    } else {
        return -1;
    }
}
bool isCorrectInputFile(ifstream &_fin);
bool isPalindromeRecursion(char*str, int i, int j);
bool isPalindrome(char*str, int i, int j);
int digitalRootRecursion(int a);
int digitalRoot(int a);
int AckermannFunctionRecursion(int n, int m);
int AckermannFunction(int n, int m);
