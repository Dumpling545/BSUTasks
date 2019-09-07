#pragma once
#include <fstream>
#include <cstring>
#include <iostream>
#include <cmath>
#include <typeinfo>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include "element.h"
#include "number.h"
#include "add.h"
#include "subtract.h"
#include "multiply.h"
#include "divide.h"
#include "stack.h"
using namespace std;

bool isCorrectBrackets(char* str);
bool isCorrectInputFile(ifstream &_fin);
char * minMaxShuntingYard(char * str);
int computeMinMaxString(char * str);
Element * shuntingYard(char * str);
double computeString(char * str);
Operation * operationFactory(char op, Element *previous);
