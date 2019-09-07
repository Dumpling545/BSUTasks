#include <iostream>
#include <string>
#include "week6.h"
using namespace std;
/**
        Реализовать 4 функции на простейшие арифметические операции
        (+, -, *, /). Каждая функция должна принимать два вещественных числа и
        возвращать результат операции в виде вещественного числа. Напишите функцию,
        которая принимает указатель на функцию в качестве параметра.
        Добавьте меню, в котором пользователь может выбрать желаемую операцию.


        Input                       Output
        ---------------------------------------------------
                                    Indexes of operations
                                    0 - addition
                                    1 - multiplication
                                    2 - subtraction
                                    3 - division
                                    4 - exit
        ---------------------------------------------------
        0                           -1.09
        11.78 -12.87

        1                           1.32
        1.1 1.2

        2                           1.005
        11.23 10.225

        3                           -1.1
        -1.21 1.1

        -1                          Incorrect value.Please re-enter:

        5                           Incorrect value.Please re-enter:
*/
int main()
{
    const int AMOUNT_OF_OPERATIONS = 4;
    const int ADD_INDEX = 0;
    const int MULT_INDEX = 1;
    const int SUB_INDEX = 2;
    const int DIV_INDEX = 3;

    double (*operations[AMOUNT_OF_OPERATIONS]) (double, double);
    operations[ADD_INDEX] = addition;
    operations[MULT_INDEX] = multiplication;
    operations[SUB_INDEX] = subtraction;
    operations[DIV_INDEX] = division;
    int index;
    cout << "Indexes of operations" << endl;
    cout << ADD_INDEX <<" - addition" <<endl;
    cout << MULT_INDEX <<" - multiplication" <<endl;
    cout << SUB_INDEX <<" - subtraction" <<endl;
    cout << DIV_INDEX <<" - division" <<endl;
    cout << AMOUNT_OF_OPERATIONS << " - exit" <<endl;
    cout << "Enter index of operation:" << endl;
    while(cin >> index){
        while(index < 0 || index > AMOUNT_OF_OPERATIONS){
            cout << "Incorrect value.Please re-enter: " << endl;
            cin >> index;
        }
        if(index == AMOUNT_OF_OPERATIONS){
            break;
        } else {
            printOperation(operations[index]);
        }
        cout <<endl;
        cout << "Enter index of operation:" << endl;
    }
    system("pause");
    return 0;
}
