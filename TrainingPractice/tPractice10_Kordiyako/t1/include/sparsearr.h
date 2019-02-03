#pragma once
#include "sa_item.h"
#include <list>
#include <iostream>

template <class T>
class SparseArr {
    public:
        SparseArr( long len ) : length( len ) {}
        T& operator []( long ind );
        void Show( const char* );
        private:
            std::list<SA_item<T> > arr;
            long length;
};
template <class T>
void SparseArr<T>::Show(const char* title) {
    std::cout << "===== " << title << " =====\n";
    typename std::list<SA_item<T>>::iterator i = arr.begin();
    typename std::list<SA_item<T>>::iterator n = arr.end();
    for (; i != n; ++i)
        std::cout << i->index << "\t" << i->info << std::endl;
}
template <class T>
T& SparseArr<T>::operator[](long ind) {
    if ((ind < 0) || (ind > length-1)) {
        std::cerr << "Error of index: " << ind << std::endl;
        SA_item<T> temp;
        return temp.info;
    }
    typename std::list<SA_item<T>>::iterator i = arr.begin();
    typename std::list<SA_item<T>>::iterator n = arr.end();
    for (; i != n; ++i)
        if (ind == i->index) return i->info;
    arr.push_back(SA_item<T>( ind, T()));
    i = arr.end();
    return (--i)->info;
}
