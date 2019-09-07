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
            if(elements == nullptr){
                elements = new T[capacity];
            }
            resize(2*size);
            for(int i = 0; i < size; i++){
                elements[i] = source[i];
                //cout << typeid(*this).name() <<" type " << typeid((*this)[i]).name() << " - " <<typeid(source).name() << endl;
            }
        }
        Vector(int defSize){
            capacity = 2*defSize;
            elements = new T[capacity];
        }
        int getSize() const{
            return size;
        }
        Vector operator+=(const Vector & v){
           // cout << &v << endl;
            if(size == v.getSize()){
                for(int i = 0; i < size; i++){
                    elements[i] += v[i];
                }
                return *this;
            } else {
                cout << "Error: vectors are not matched: " <<size <<", " << v.getSize() <<endl;
                throw "Error: vectors are not matched";
            }
        }

        Vector operator-=(const Vector & v){
            if(size == v.getSize()){
                for(int i = 0; i < size; i++){
                    elements[i] -= v[i];
                }
                return *this;
            } else {
                cout << "Error: vectors are not matched" <<endl;
                throw "Error: vectors are not matched";
            }
        }

        Vector operator*=(const int& scalar){
            for(int i = 0; i < size; i++){
                elements[i] *= scalar;
            }
            return *this;
        }

        Vector operator/=(const int& scalar){
            for(int i = 0; i < size; i++){
                elements[i] /= scalar;
            }
            return *this;
        }

        const Vector operator+(const Vector & v) const{
            return Vector(*this)+= v;
        }

        const Vector operator-(const Vector& v) const{
            return Vector(*this)-= v;
        }

        const Vector operator*(const int scalar) const{
            return Vector(*this)*= scalar;
        }

        const Vector operator/(const int scalar) const{
            return Vector(*this)/= scalar;
        }

        const Vector operator=(const Vector& v){
            int s = v.getSize();
            resize(2*s);
            for(int i = 0; i < s; i++){
                (*this)[i] = v[i];
            }
            return (*this);
        }
        const bool operator==(const Vector& v) const;
        const bool operator!=(const Vector& v) const;

          T& operator[](const int index) const{
            if(index < 0 || index >= size){
                cout << "Error: index is out of the array" <<endl;
                throw "Error: index is out of the array";
            } else {
                return elements[index];
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
                    for(int i = capacity; i < newCapacity; i++){
                        temp[i] = 0;
                    }
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
                cout << "Error: new size for vector should be greater than 0" <<endl;
            }
        }
    private:
        int size = 0;
        int capacity = 1000;
        T * elements = nullptr;
};
