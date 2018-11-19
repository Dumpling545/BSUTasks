#pragma once
#include <iostream>
/**Составить описание класса для определения одномерных массивов целых чисел (векторов).
Предусмотреть возможность обращения к отдельному элементу массива с контролем выхода за пределы массива,
 возможность задания произвольных границ индексов при создании объекта,
 возможность выполнения операций поэлементного сложения и вычитания массивов с одинаковыми границами индексов,
 умножения и деления всех элементов массива на скаляр, вывода на экран элемента массива по заданному индексу,
 вывода на экран всего массива. Написать программу, демонстрирующую работу с этим классом.
Программа должна содержать меню, позволяющее осуществить проверку всех методов класса.*/
using namespace std;
template <class T>
class Vector
{
    public:
        Vector(){
            elements = new T[capacity];
        }
        Vector(const Vector &source){
            capacity =  2*source.getSize();
            resize(capacity);
            for(int i = 0; i < capacity; i++){
                (*this)[i] = source[i];
            }
        }
        Vector(int defSize){
            capacity = 2*defSize;
            elements = new T[capacity];
        }
        int getSize() const{
            return size;
        }
        Vector operator+=(const Vector& v){
            if(size == v.getSize()){
                for(int i = 0; i < size; i++){
                    elements[i] += v[i];
                }
                return *this;
            } else {
                cout << "Error: vectors are not matched" <<endl;
                throw "Error: vectors are not matched";
            }
        }

        Vector operator-=(const Vector& v){
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

        const Vector operator+(const Vector& v) const;

        const Vector operator-(const Vector& v) const;

        const Vector operator*(const int& scalar) const;

        const Vector operator/(const int& scalar) const;

        const Vector operator=(const Vector& v);
        const bool operator==(const Vector& v) const;
        const bool operator!=(const Vector& v) const;

          T& operator[](const int index){
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
                capacity = size*2;
                resize(capacity);
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
                size = newCapacity;
                capacity = newCapacity;
            } else {
                cout << "Error: new size for vector should be greater than 0" <<endl;
            }
        }
    private:
        int size = 0;
        int capacity = 1000;
        T * elements;
};
