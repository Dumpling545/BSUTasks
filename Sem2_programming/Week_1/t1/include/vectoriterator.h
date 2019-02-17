#pragma once
#include "vector.h"
template<class T>
class VectorIterator
{
    public:
        VectorIterator(Vector<T> * vector) {
            this->vector = vector;
        }
        bool isEnd() {
            return current == vector->getSize() - 1;
        }
        bool isBegin(){
            return current == 0;
        }
        void toBegin(){
            current = 0;
        }
        void toEnd(){
            current = vector->getSize() - 1;
        }
        operator T () {
            return (*vector)[current];
        }
        VectorIterator operator ++(int){
            VectorIterator previous = *this;
            ++current;
            return previous;
        }
        VectorIterator operator --(int){
            VectorIterator previous = *this;
            --current;
            return previous;
        }
    private:
        Vector<T> * vector;
        int current = 0;
};

