#include <iomanip>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "arrays.h"
using namespace std;
/**
    –еализовать 4 функции. ƒобавьте меню, в котором пользователь может выбрать желаемую операцию:

        —оздать функцию, вставл€ющую строку в двумерный динамический массив в указанную позицию.
        —оздать функцию, вставл€ющую столбец в двумерный динамический массив в указанную позицию.
        —оздать функцию, удал€ющую заданную строку двумерного динамического массива.
        —оздать функцию, удал€ющую заданный столбец двумерного динамического массива.


    Input                           Output
    -----------------------------------------------------------------
                                    99 34 24 24 15
                                    16 16 26 87  3
                                     1 73 93 92 33
                                    23 76 81 35 83
                                    56 15 53 89 50
                                    Indexes of operations
                                    0 - insert row
                                    1 - insert column
                                    2 - delete row
                                    3 - delete column
                                    4 - exit
    -----------------------------------------------------------------
    0                               99    34    24    24    15
    1                                1     2     3     4     5
    1 2 3 4 5                       16    16    26    87     3
                                     1    73    93    92    33
                                    23    76    81    35    83
                                    56    15    53    89    50

    1                               99    34    10    24    24    15
    2                               10    20    20    30    40    50
    10 20 30 40 50 60               16    16    30    26    87     3
                                     1    73    40    93    92    33
                                    23    76    50    81    35    83
                                    56    15    60    53    89    50

    2                               99    34    10    24    24    15
    3                               10    20    20    30    40    50
                                    16    16    30    26    87     3
                                    23    76    50    81    35    83
                                    56    15    60    53    89    50

    3                               99    34    10    24    15
    4                               10    20    20    30    50
                                    16    16    30    26     3
                                    23    76    50    81    83
                                    56    15    60    53    50

    -1                              Incorrect index of operation.

    5                               Incorrect index of operation.

    1                               Incorrect number. Re-enter:
    6

    1                               Incorrect number. Re-enter:
    -1


*/
int main()
{
    int n = 5;
    int m = 5;
    int** matrix =createMatrixWithRandomValues(n,m);
    const int INSERT_ROW = 0;
    const int INSERT_COLUMN = 1;
    const int DELETE_ROW = 2;
    const int DELETE_COLUMN = 3;
    const int EXIT = 4;
    int index;
    cout << "Indexes of operations" << endl;
    cout << INSERT_ROW <<" - insert row" <<endl;
    cout << INSERT_COLUMN <<" - insert column" <<endl;
    cout << DELETE_ROW <<" - delete row" <<endl;
    cout << DELETE_COLUMN <<" - delete column" <<endl;
    cout << EXIT << " - exit" <<endl;
    bool notEnded = true;
    int position;
    int* ar;
    while(notEnded){
        cout << "Enter index of operation:" << endl;
        cin >> index;
        switch(index){
            case INSERT_ROW:
                enterInteger(position, "insertion index", [n,m](int x) {return x >= 0 && x < n;});
                ar = enterArray(m);
                insertRow(matrix, n, m, ar, position);
                delete []ar;
                break;
            case INSERT_COLUMN:
                enterInteger(position, "insertion index", [n,m](int x) {return x >= 0 && x < m;});
                ar = enterArray(n);
                insertColumn(matrix, n, m, ar, position);
                delete []ar;
                break;
            case DELETE_ROW:
                enterInteger(position, "deletion index", [n,m](int x) {return x >= 0 && x < n;});
                deleteRow(matrix, n, m, position);
                break;
            case DELETE_COLUMN:
                enterInteger(position, "deletion index", [n,m](int x) {return x >= 0 && x < m;});
                deleteColumn(matrix, n, m, position);
                break;
            case EXIT:
                notEnded = false;
                break;
            default:
                cout << "Incorrect index of operation." << endl;
                break;

        }
        if(index < EXIT && index >= 0){
            cout << "Result: " <<endl;
            printMatrix(matrix, n, m, 10000);
        }
        cout <<endl;
    }
    return 0;
}
