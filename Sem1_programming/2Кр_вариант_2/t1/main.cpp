#include<iostream>
#include<fstream>
#include <cstdlib>
#include <cstring>
#include "polynomial.h"
#include "queue.h"
#include "vector.h"
#include "header.h"
using namespace std;
/**
1. Разработать шаблон класса Queue.

2. Разработать шаблон класса «Многочлен» – Polynom степени n .
Написать несколько конструкторов, в том числе конструктор копирования.
Реализовать методы для вычисления значения полинома; сложения, вычитания.
Перегрузить операции сложения, вычитания, индексирования, присваивания.

3. Прочитать коэффициенты нескольких полиномов из файла.
Создать очередь объектов класса. Передать его в функцию,
вычисляющую сумму полиномов степени, кратной 3 и возвращающую
полином-результат, который выводится на экран в головной программе.
*/
ifstream fin("input.txt");
ofstream fout("output.txt");
int main()
{
    if(isCorrectInputFile(fin)){
        Queue<Polynomial<int>> q;
        char * temp;
        while(fin.getline(temp, 1000)){
            Vector<int> v;
            char * token = strtok (temp," ");
            while (token != NULL)
            {
                v.push_back((int)atoi(token));
                token = strtok (NULL, " ");
            }
            q.push(Polynomial<int>(v, 0));
        }
        Polynomial<int> poly = computePolynomials<int>(q);
        poly.setArgument(0);
        fout << poly.calculate() << endl;
    }
    return 0;
}
