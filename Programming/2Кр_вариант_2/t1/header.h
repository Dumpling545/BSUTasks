#pragma once
#include "polynomial.h"
#include <fstream>
#include <iostream>
#include "queue.h"
using namespace std;
bool isCorrectInputFile(ifstream &_fin);
template<class T>
Polynomial<T> computePolynomials(Queue<Polynomial<T>> polynomials){
    Polynomial<T> res;
    while(!polynomials.isEmpty()){
        if(polynomials.first().getPower() % 3 == 0){
            cout << polynomials.first().getPower() <<endl;
            res+=polynomials.first();
        }
        polynomials.pop();
    }
    return res;
}
