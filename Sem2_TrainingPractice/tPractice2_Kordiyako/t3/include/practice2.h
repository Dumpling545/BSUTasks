#pragma once
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <cstring>
#include <set>
#include "student.h"
//t1
bool isCorrectInputFile(std::ifstream &_fin);
template<typename T, typename A>
void fillVector(std::istream &_fin, std::vector<T, A> &vect){
    T elem;
    while(_fin >> elem){
        vect.push_back(elem);
    }
}
void printMax(std::vector<int> &vect);
template<typename T>
void enterElement(T &i, std::string name = "element"){
    std::cout << "Enter "<<name<<": " << '\n';
    std::cin >> i;
}
template<typename T, class InputIterator>
void printInterval(InputIterator b,InputIterator e){
    std::for_each<InputIterator>(b, e, [](T elem){ std::cout << elem << " ";});
    std::cout <<'\n';
}

void printAmountOfElementsEqualTo(std::vector<int> &vect, int i);
void printAmountOfElementsBiggerThan(std::vector<int> &vect, int i);
void printAmountOfElements(std::vector<int> &vect);
void printSum(std::vector<int> &vect);
void printAverage(std::vector<int> &vect);

void getWordsStartWith(std::vector<std::string> &dest, const std::vector<std::string> &src, char c);
void deleteWordsStartWith(std::vector<std::string> &vect, char c);
void countWordRepeats(std::map<std::string, int> &dest, const std::vector<std::string> &src);

int countStudentsWithMark(std::vector<Student> vect, double mark);
