#include <iostream>
#include "arrays.h"
#include "lab4.h"
using namespace std;
/**
    Дан массив целых чисел, в котором все числа кроме одного встречаются четное количество раз,
    одно число встречается нечетное количество раз. Найти это число.

    Input                                   Output
    -------------------------------------------------------------------
    -1                                      Incorrect natural number. Re-enter:

    15                                      4
    1 4 2 3 3 2 4 1 2 1 4 3 1 3 2


*/

int main()
{
    int n;
    cout << "Enter n:" << endl;
    enterNatural(n);
    int *ar = enterArray(n);
    cout << oddTimesNumberInArrayByXor(ar, n) << endl;
    //cout << oddTimesNumberInArrayBySort(ar, n) << endl;
    system("pause");
    return 0;
}
