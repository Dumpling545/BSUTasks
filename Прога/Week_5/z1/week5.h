#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>

int sumRow(int ** matrix, int n, int index);
int sumColumn(int ** matrix, int n, int index);
bool isMagic(int ** matrix, int n);
int enterMatrixWithTwoes(int **matrix, int n);
void printMatrix(int **matrix, int n, int maxValue);
int** createMatrix(int n);
void enterNatural(int &n);
int* BinaryEnter(int *ar, int n, int value, int _start = 0, int _ending = 0);
int* enterArray(int n);
void enterNatural(int &n, string inputName);
int* enterArray(int n, string inputName);
void  insertionSortWithBS(int *ar, int n);
int*  normalizeSet(int *unnormalizedSet, int &n);
int* isSubstring(int *baseString, int baseStringSize, int *predictingSubstring, int predictingSubstringSize);
bool isSubset(int *baseSet, int baseSetSize, int *predictingSubset, int predictingSubsetSize);
