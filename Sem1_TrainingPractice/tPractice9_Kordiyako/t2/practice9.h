#pragma once
#include <fstream>
#include <cstring>
#include <iostream>
#include <cmath>
#include "stack.h"
using namespace std;

bool isCorrectBrackets(char* str);
char * minMaxShuntingYard(char * str);
int computeMinMaxString(char * str);
int triangleType(int a = 0, int b = 0, int c = 0);