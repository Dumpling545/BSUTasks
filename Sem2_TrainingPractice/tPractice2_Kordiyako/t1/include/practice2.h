#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
//t1
bool isCorrectInputFile(std::ifstream &_fin);
void fillVector(std::istream &_fin, std::vector<int> &vect);
void printMax(std::vector<int> &vect);
void enterInteger(int &i);
void printAmountOfElementsEqualTo(std::vector<int> &vect, int i);
void printAmountOfElementsBiggerThan(std::vector<int> &vect, int i);
void printAmountOfElements(std::vector<int> &vect);
void printSum(std::vector<int> &vect);
void printAverage(std::vector<int> &vect);
