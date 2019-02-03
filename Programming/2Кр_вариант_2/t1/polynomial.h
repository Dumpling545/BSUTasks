#pragma once
#include<iostream>
#include "vector.h"
template<class T>
class Polynomial{
    public:
        Polynomial(){}
        Polynomial(Vector<T> coefficients, T argument){
            this->coefficients = new Vector<T>(coefficients);
            this->argument = argument;
        }
        Polynomial(const Polynomial &source){
            coefficients = new Vector<T>(*(source.coefficients));
            argument = source.getArgument();
        }
        T calculate() {
            int length = coefficients->getSize();
            T pow_arg = argument;
            T res;
            if(length > 0){
                res = (*coefficients)[0];
            } else {
                throw "Calculating null polynomial!";
            }
            for(int i = 1; i < length; i++){
                res +=(*coefficients)[i] * pow_arg;
                pow_arg *= argument;
            }
            return res;
        }
        Polynomial operator+=(const Polynomial& pol){
            int length1 = coefficients->getSize();
            int length2 = pol.coefficients->getSize();
            Polynomial p1 = Polynomial(*this);
            Polynomial p2 = Polynomial(pol);
            if(length1 > length2){
                for(int i = length2; i < length1; i++){
                    p2.coefficients->push_back(0);
                }
            } else {
                for(int i = length1; i < length2; i++){
                    p1.coefficients->push_back(0);
                }
            }
            delete coefficients;
            coefficients = new Vector<T>((*p1.coefficients) + (*p2.coefficients));
            return (*this);
        }
        Polynomial operator-=(const Polynomial& pol){
            int length1 = coefficients->getSize();
            int length2 = pol.coefficients->getSize();
            Polynomial p1 = Polynomial(*this);
            Polynomial p2 = Polynomial(pol);
            if(length1 > length2){
                for(int i = length2; i < length1; i++){
                    p2.coefficients->push_back(0);
                }
            } else {
                for(int i = length1; i < length2; i++){
                    p1.coefficients->push_back(0);
                }
            }
            delete coefficients;
            coefficients = new Vector<T>((*p1.coefficients) - (*p2.coefficients));
            return (*this);
        }
        const Polynomial operator+(const Polynomial& pol) const{
            return Polynomial(*this)+= pol;
        }
        const Polynomial operator-(const Polynomial& pol) const{
            return Polynomial(*this)-= pol;
        }
        const Polynomial operator=(const Polynomial& pol){
            delete coefficients;
            coefficients = new Vector<T>(*(pol.coefficients));
            argument = pol.getArgument();
        }
        void setArgument(T argument){
            this->argument = argument;
        }
        T getArgument() const{
            return argument;
        }
        T& operator[](const int index) const{
            try{
                return (*coefficients)[index];
            } catch (char *s){
                cout << s << endl;
            }
        }
        int getPower(){
            return coefficients->getSize() - 1;
        }
    private:
        Vector<T> * coefficients;
        T argument;
};
