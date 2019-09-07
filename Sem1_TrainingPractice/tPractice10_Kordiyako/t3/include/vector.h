#pragma once
#include <typeinfo>
#include <iostream>
using namespace std;
template <class T>
class Vector
{
    public:
        Vector(){
            elements = new T[capacity];
        }
        Vector(const Vector & source){
            size = source.getSize();
            delete [] elements;
            elements = new T[capacity];
            resize(2*size);
            for(int i = 0; i < size; i++){
                elements[i] = source[i];
            }
        }
        Vector(int defSize, T fillWith){
            capacity = 2*defSize;
            elements = new T[capacity];
            size = defSize;
            for(int i = 0; i < size; i++){
                elements[i] = fillWith;
            }
        }
        int getSize() const{
            return size;
        }
        const Vector operator=(const Vector& v){
            int s = v.getSize();
            resize(2*s);
            for(int i = 0; i < s; i++){
                (*this)[i] = v[i];
            }
            return (*this);
        }

          T& operator[](const int index) const{
            if(index < 0 || index >= size){
                throw "Error: index is out of the array";
            } else {
                return elements[index];
            }
        }
        void push_at(int position, T element){
            if(position >= 0 && position < size){
                if(size == capacity){
                    resize(size*2);
                }
                for(int i = size; i > position; i--){
                    elements[i] = elements[i-1];
                }
                size++;
                elements[position] = element;
            } else {
                throw "Error: index is out of the array";
            }
        }
        void pop_back(){
            if(size > 0){
                --size;
            } else {
                cout << "Warning: cannot delete element from empty array" <<endl;
            }
        }
        void push_back(T element){
            if(size < capacity){
                elements[size] = element;
                size++;
            } else {
                resize(size*2);
                elements[size] = element;
                size++;
            }
        }
        void resize(int newCapacity){
            T * temp = new T[newCapacity];
            if(newCapacity > 0){
                if(newCapacity > capacity){
                    for(int i = 0; i < capacity; i++){
                        temp[i] = elements[i];
                    }
                    /*for(int i = capacity; i < newCapacity; i++){
                        temp[i] = 0;
                    }*/
                } else {
                    for(int i = 0; i <newCapacity;i++){
                        temp[i] = elements[i];
                    }
                }
                elements = new T[newCapacity];
                for(int i = 0; i < newCapacity; i++){
                    elements[i] = temp[i];
                }
                capacity = newCapacity;
            } else {
                cout << "Warning: new size for vector should be greater than 0" <<endl;
            }
        }
    private:
        int size = 0;
        int capacity = 1000;
        T * elements = nullptr;
};
