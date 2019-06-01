#pragma once
#include<set>
#include<string>
#include<cmath>
#include<iostream>
#include<fstream>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include<list>
#include "flowerbed.h"
bool isCorrectInputFile(std::ifstream &_fin);

template<typename T>
void fillList(std::istream &_fin, std::list<T> &vect){
    T elem;
    while(_fin >> elem){
        vect.push_back(elem);
    }
}

template<typename T, class InputIterator>
void printInterval(std::ostream &stream, InputIterator b, InputIterator e){
    std::for_each<InputIterator>(b, e, [&stream](T elem){ stream << elem <<'\n';});
}

template<typename T>
void enterElement(T &i, std::string name = "element"){
    std::cout << "Enter "<<name<<": " << '\n';
    std::cin >> i;
}

void sortByShape(std::list<Flowerbed> & flowerbeds);
void convertListToMap(std::list<Flowerbed> src,
                      std::map<int, Flowerbed> & dest);

void getUniqueShapes(std::map<int, Flowerbed> flowerbeds,
                     std::set<std::string> & shapes);

struct setStringComparator{
    bool operator()(const std::set<std::string> &a,
                    const std::set<std::string> &b) const;
};
