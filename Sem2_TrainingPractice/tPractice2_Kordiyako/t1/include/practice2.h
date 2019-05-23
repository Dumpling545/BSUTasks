#pragma once
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
//t1
bool isCorrectInputFile(std::ifstream &_fin);

template<typename T, typename A>
void fillVector(std::istream &_fin, std::vector<T, A> &vect){
    T elem;
    while(_fin >> elem){
        vect.push_back(elem);
    }
}

template<typename T>
void enterElement(T &i, std::string name = "element"){
    std::cout << "Enter "<<name<<": " << '\n';
    std::cin >> i;
}

template<typename T, class InputIterator>
void printInterval(InputIterator b, InputIterator e){
    std::for_each<InputIterator>(b, e, [](T elem){ std::cout << elem << " ";});
    std::cout <<'\n';
}

//task 1
int getMax(std::vector<int> &vect);
int getAmountOfElementsEqualTo(std::vector<int> &vect, int i);
int getAmountOfElementsBiggerThan(std::vector<int> &vect, int i);
int getAmountOfElements(std::vector<int> &vect);
int getSum(std::vector<int> &vect);
double getAverage(std::vector<int> &vect);

void getWordsStartWith(std::vector<std::string> &dest,
                       const std::vector<std::string> &src, char c);
void deleteWordsStartWith(std::vector<std::string>
                          &vect, char c);
void countWordRepeats(std::map<std::string, int> &dest,
                      const std::vector<std::string> &src);
