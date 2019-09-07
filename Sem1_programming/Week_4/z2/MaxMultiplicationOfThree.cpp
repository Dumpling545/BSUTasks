#include <iostream>
#include "arrays.h"
#include "lab4.h"
using namespace std;
/**
    Дан массив целых чисел, из этой последовательности целых чисел выбрать три числа, произведение которых максимально

    Input                                   Output
    -------------------------------------------------------------------
    0                                       Incorrect natural number. Re-enter:

    10                                      360
    -9 5 -8 4 -7 3 -6 2 -5 1

    10                                      336
    -9 8 7 6 5 4 3 2 1 0

    10                                      504
    9 0 8 1 7 2 6 3 5 4

*/

int main()
{
    int n;
    cout << "Enter n:" << endl;
    enterNatural(n);
    int * ar = enterArray(n);
    cout << maxMultiplication(ar, n)<<endl;
    system("pause");
    return 0;
}
