#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;
int** createMatrix(int n, int m);
int maxAtMatrix(int ** matrix, int n, int m);
int minAtMatrix(int ** matrix, int n, int m);
int **fPrintMatrix(ofstream &fout, int ** matrix, int n, int m);
void fillMatrixUniqueNumbers(int **matrix, int n, int m);
int ** fCreateMatrix(ifstream &fin, int n, int m);
int countUniqueMatrix(int **matrix, int n, int m);
int countSignChangesMatrix(int **matrix, int n, int m);
int countColumnPairsMatrix(int ** matrix, int n, int m);
int countRowPairsMatrix(int ** matrix, int n, int m);
int sumRow(int ** matrix, int n, int index);
int maxRowIndex(int ** matrix, int n);
int minRowIndex(int ** matrix, int n);
