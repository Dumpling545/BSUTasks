#include <iostream>
#include "arrays.h"
#include "week5.h"

/**
    Дана квадратная матрица n-го порядка,
    состоящая из целых чисел. Определить является ли она магическим
    квадратом (Магический квадрат — квадратная таблица n × n, заполненная n2
    различными числами таким образом, что сумма чисел в каждой строке,
    каждом столбце и на обеих диагоналях одинакова). Для решения задачи
    использовать функцию поиска суммы элементов i-того столбца и строки,
    массив передается в функцию через указатель.

    Input                       Output
    ----------------------------------------------
    1                           Incorrect number(should be greater than 1). Re-enter:

    3                           This matrix is not magic
    1 2 3
    4 5 6
    7 8 9

    3                           This matrix is magic
    4 9 2
    3 5 7
    8 1 6

    4                           This matrix is not magic
    1 1 1 1
    1 1 1 1
    1 1 1 1
    1 1 1 1
*/
using namespace std;

int main()
{
    int n;
    cout << "Enter n:" <<endl;
    cin >> n;
    while(n < 2){
        cout << "Incorrect number(should be greater than 1). Re-enter: " << endl;
        cin >> n;
    }
    int **ar = new int*[n];
    cout << "Enter matrix (n x n): " <<endl;
    for(int i = 0; i < n; i++){
        ar[i] = new int[n];
        for(int j = 0; j < n; j++){
            cin >> ar[i][j];
        }
    }
    cout << "This matrix is ";
    if(!isMagic(ar, n)){
        cout << "not ";
    }
    cout << "magic"<<endl;
    return 0;
}
