#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "arrays.h"
using namespace std;
double addition(double a, double b);
double multiplication(double a, double b);
double subtraction(double a, double b);
double division(double a, double b);
void printOperation(double (*operation)(double, double));
int* findPrimes(int *a, int n, int &newIndex);
int * findEvens(int *a, int n, int &newIndex);
int * findMultiplesOfThree(int *a, int n, int &newIndex);
void printOperation(int*ar, int n, int* (*operation)(int*, int, int&));
void printMatrix(int** matrix, int n, int m, int maxValue);
void fillMatrixWithRandomValues(int **matrix, int n, int m, bool shouldPrint);
int ** createMatrixWithRandomValues(int n, int m, bool shouldPrint = true);
void insertRow(int **& matrix, int &n, int m, int *newRow, int position);
void insertColumn(int **& matrix, int n, int &m, int *newColumn, int position);
void deleteRow(int **& matrix, int &n, int m, int position);
void deleteColumn(int **& matrix, int n, int &m,  int position);