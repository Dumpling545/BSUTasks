#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>

//#ifndef ARRAYS_H_INCLUDED
//#define ARRAYS_H_INCLUDED

long long getSwaps();
long long getCompares();
void swapElements(int &a, int &b);
void  selectionSort(int *ar, int n);
void  insertionSort(int *ar, int n);
void  bubbleSort(int *ar, int n);
void  coctailSort(int *ar, int n);
void  oddEvenSort(int *ar, int n);
int* generateArray(int n);
void printArray(int *ar, int n);
int* enterArray(int n);
void copyArray(int *arFrom, int *arTo, int n);
void reverseArray(int *ar, int n);
//#endif // ARRAYS_H_INCLUDED
