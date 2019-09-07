#pragma once
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iomanip>
using namespace std;
void fPrintLettersDigitsOthers(ofstream& _fout, char * str);
char * removeSubStr(char* str, char* word);
int maxAtMatrix(int ** matrix, int n, int m);
int minAtMatrix(int ** matrix, int n, int m);
void printTwoLetterCombinations(ofstream& _fout, char * str);
void reverseWords(ofstream &_fout, char* str);
int findSubstr(char* str, char*sub);
void replaceWith(char* &str, char* oldSubstr, char* newSubstr);