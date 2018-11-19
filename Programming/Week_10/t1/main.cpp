#include <iostream>
#include "rational.h"
using namespace std;
/**
    (5 баллов) Рациональная (несократимая) дробь представляется парой целых чисел (a,b),
    где a – числитель, b – знаменатель. Создать класс Rational для работы с рациональными дробями.
    Реализовать конструкторы: копирования и инициализации, а также методы:
    сложение add, (a,b) + (c,d) = (ad+bc,bd);
    умножение mul, (a,b) * (c,d) = (ac, bd);
    деление div, (a,b)/(c,d) = (ad,bc);
    сравнение equal, greater, less;
    вывод print.
    Зам. Реализовать приватную функцию сокращения дроби reduce, которая обязательно
    вызывается при выполнении арифметических операций.
*/
int main()
{
    Rational r1(-3003,2210);
    Rational r2(-1,-3);
    r1.print(cout);
    cout << " + ";
    r2.print(cout);
    cout << " = ";
    (r1 + r2).print(cout);
    cout << endl;
    r1.print(cout);
    cout << " - ";
    r2.print(cout);
    cout << " = ";
    (r1 - r2).print(cout);
    cout << endl;
    r1.print(cout);
    cout << " * ";
    r2.print(cout);
    cout << " = ";
    (r1 * r2).print(cout);
    cout << endl;
    r1.print(cout);
    cout << " / ";
    r2.print(cout);
    cout << " = ";
    (r1 / r2).print(cout);
    cout << endl;
    if(r1 > r2){
        r1.print(cout);
        cout << " > ";
        r2.print(cout);
    } else if(r1 < r2){
        r1.print(cout);
        cout << " < ";
        r2.print(cout);
    } else {
        r1.print(cout);
        cout << " == ";
        r2.print(cout);
    }
    return 0;
}
