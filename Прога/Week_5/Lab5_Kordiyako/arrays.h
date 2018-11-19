#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
//#ifndef ARRAYS_H_INCLUDED
//#define ARRAYS_H_INCLUDED
using namespace std;
int getSwaps();
int getCompares();
void swapElements(int &a, int &b);
void  selectionSort(int *ar, int n);
void  insertionSort(int *ar, int n);
void  bubbleSort(int *ar, int n);
void  coctailSort(int *ar, int n);
void  oddEvenSort(int *ar, int n);
int* generateArray(int n);
void printArray(int *ar, int n);
void enterInteger(int &n, string inputName, bool (*match)(int));
void enterNatural(int &n);
void enterNatural(int &n, string inputName);
int* enterArray(int n);
int* enterArray(int n, string inputName);
void fillArray(int *ar,int n);
void copyArray(int *arFrom, int *arTo, int n);
//#endif // ARRAYS_H_INCLUDED
