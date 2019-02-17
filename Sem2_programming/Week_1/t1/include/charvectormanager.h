#pragma once
#include "vector.h"
#include "vectoriterator.h"
class CharVectorManager
{
    public:
        CharVectorManager(Vector<char> * vector);
        void print();
        void printReverse();
    private:
        Vector<char> * vector;
};
