#include <iostream>
#include "arrays.h"
#include "lab4.h"
using namespace std;
/**Добавить к некоторой последовательности  A=a(i), i=1..n, n<=100,
    наименьшее  число элементов,  чтобы  получить  арифметическую прогрессию (например, 22 1  36  -> 1  8 15 22 29 36).

    Input                                   Output
    ------------------------------------------------------------------------------------------------
    2                                       Incorrect number (should be greater than two). Re-enter:

    3                                       1 8 15 22 29 36
    22 1 36

    3                                       1 8 15
    8 1 15

    3                                       1 2 3 4 5 6 7
    1 7 2

    3                                       -7 -5 -3 -1 1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31
    -7 83 15                                33 35 37 39 41 43 45 47 49 51 53 55 57 59 61 63 65 67 69
                                            71 73 75 77 79 81 83

    */
int main()
{
    int n;
    cout << "Enter n:"<<endl;
    cin >> n;
    while(n < 3){
        cout << "Incorrect number (should be greater than two). Re-enter: " << endl;
        cin >> n;
    }
    int *ar = enterArray(n);
    selectionSort(ar, n);
    int d = findStep(ar, n);
    int a = ar[0];
    cout << a << " ";
    while(a < ar[n-1]){
        cout << a + d << " ";
        a+=d;
    }
    system("pause");
    return 0;
}
