#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;
int sumRow(int ** matrix, int n, int index);
int sumColumn(int ** matrix, int n, int index);
bool isMagic(int ** matrix, int n);
int enterMatrixWithTwoes(int **matrix, int n);
void printMatrix(int **matrix, int n, int maxValue);
int** createMatrix(int n, int m);
int** createMatrix(int n);
void enterNatural(int &n);
int* BinaryEnter(int *ar, int n, int value, int _start = 0, int _ending = 0);
void  insertionSortWithBS(int *ar, int n);
int*  normalizeSet(int *unnormalizedSet, int &n);
int* isSubstring(int *baseString, int baseStringSize, int *predictingSubstring, int predictingSubstringSize);
bool isSubset(int *baseSet, int baseSetSize, int *predictingSubset, int predictingSubsetSize);
bool CanGo(int fromValue, int toValue);
void fillMatrix(int**matrix, int n, int m, int value);
int ** BFS(int**matrix, int n, int m, int x_start, int y_start, bool (*canGo)(int, int));
pair<int, int>  mostDistantElement(int**matrix, int n, int m, int x0, int y0);
bool** canReach(int**matrix, int n, int m, int x0, int y0);
bool matchMatrix(int value);
void fillMatrixWithRandomValues(int **matrix, int n, int m, bool shouldPrint = true);
