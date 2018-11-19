#include <iostream>
#include "arrays.h"
#include "week6.h"
/**
    Реализовать 3 функции каждая из которых принимает указатель на массив и
    количество элементов и возвращает указатель на новый массив. Первая функция
    ищет простые числа и заносит их в новый массив, вторая – все числа кратные трем,
    третья – все четные числа. Напишите функцию, которая принимает указатель на функцию в качестве параметра.
    Добавьте меню, в котором пользователь может выбрать желаемую операцию.

    Input                   Output
    -----------------------------------------------------------------------
                            Indexes of operations
                            -1 - generate new array
                            0 - find primes in array
                            1 - find evens in array
                            2 - find multiples of three in array
                            3 - exit
                            Default array:
                            6709 2703 1809 1767 194 7084 5071 1372 3186 235
    ------------------------------------------------------------------------
    -1                      9390 2553 8230 1412 1547 6897 4490 144 3250 8943
    10

    0

    1                       9390 8230 1412 4490 144 3250

    2                       9390 2553 6897 144 8943

    -2                      Incorrect value. Please re-enter:

    4                       Incorrect value. Please re-enter:

*/
using namespace std;
int main()
{
    const int AMOUNT_OF_OPERATIONS = 3;
    const int GENERATE_NEW_ARRAY = -1;
    const int FIND_PRIMES_INDEX = 0;
    const int FIND_EVENS_INDEX = 1;
    const int FIND_THREES_INDEX = 2;
    int n = 10;
    int* (*operations[AMOUNT_OF_OPERATIONS]) (int*, int, int&);
    operations[FIND_PRIMES_INDEX] = findPrimes;
    operations[FIND_EVENS_INDEX] = findEvens;
    operations[FIND_THREES_INDEX] = findMultiplesOfThree;
    int index;
    cout << "Indexes of operations" << endl;
    cout << GENERATE_NEW_ARRAY << " - generate new array" << endl;
    cout << FIND_PRIMES_INDEX <<" - find primes in array" <<endl;
    cout << FIND_EVENS_INDEX <<" - find evens in array" <<endl;
    cout << FIND_THREES_INDEX <<" - find multiples of three in array" <<endl;
    cout << AMOUNT_OF_OPERATIONS << " - exit" <<endl;
    cout << "Enter index of operation:" << endl;
    cout << "Default array:" <<endl;
    int *a = generateArray(n);
    printArray(a, n);
    cout <<endl;
    cout << "Enter index of operation:" << endl;
    while(cin >> index){
        while(index < -1 || index > AMOUNT_OF_OPERATIONS){
            cout << "Incorrect value. Please re-enter: " << endl;
            cin >> index;
        }
        if(index == AMOUNT_OF_OPERATIONS){
            break;
        } else if(index == GENERATE_NEW_ARRAY){
            cout << "Enter size of array:" << endl;
            cin >> n;
            delete [] a;
            a = generateArray(n);
            cout << "New array:" << endl;
            printArray(a, n);
        } else {
            cout << "Result: " <<endl;
            printOperation(a,n,operations[index]);
        }
        cout <<endl;
        cout << "Enter index of operation:" << endl;
    }
    delete [] a;
    system("pause");
    return 0;
}
