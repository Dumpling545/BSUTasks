#pragma once
#include <fstream>
#include <cstring>
#include <iostream>
#include <cmath>
#include "stack.h"
using namespace std;

bool isCorrectBrackets(char* str);
bool isCorrectInputFile(ifstream &_fin);
char * minMaxShuntingYard(char * str);
int computeMinMaxString(char * str);
