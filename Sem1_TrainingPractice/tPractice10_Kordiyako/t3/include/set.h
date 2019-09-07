#pragma once
#include "vector.h"
template <class T>
class Set
{
    public:
        Set() {}
        void add(T element){
            if(cardinality() == 0){
                elements.push_back(element);
            }else {
                int pos = where(element);
                if(pos == cardinality()){
                    elements.push_back(element);
                } else if(elements[pos] != element){
                    elements.push_at(pos, element);
                } else {
                    throw "Set has already included this element";
                }
            }
        }
        void remove(T element){
            int size = cardinality();
            if(size == 0){
                throw "Set is empty";
            }
            int pos = where(element);
            if(pos < size && elements[pos] == element){
                for(int i = pos; i < size-1; i++){
                    elements[i] = elements[i+1];
                }
                elements.pop_back();
            } else {
                throw "It's not an element of a set";
            }
        }
        int cardinality(){
            return elements.getSize();
        }
        bool included(T element){
            return elements[where(element)] == element;
        }
        Vector<T> get(){
            return elements;
        }
    private:
        Vector<T> elements;
        int where(T element){
            int left_border = 0;
            int right_border = elements.getSize()-1;
            if(elements[right_border] < element){
                return right_border+1;
            }
            while(right_border - left_border > 1){
                int avg = (left_border + right_border)/2;
                if(elements[avg] >= element){
                    right_border = avg;
                } else {
                    left_border = avg;
                }
            }
            return right_border;
        }
};
