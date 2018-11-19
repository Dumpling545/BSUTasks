#include <iostream>
#include <fstream>
#include "practice6.h"
using namespace std;
/**
    Написать рекурсивную функцию для вычисления значения так называемой функции Аккермана для неотрицательных чисел n и m.
    Функция Аккермана A(n, m) определяется следующим образом:

    m + 1, если n = 0;
    A(n, m) = А(n - 1, 1), если n ≠ 0, m = 0;
    A(n - 1, A(n, m- 1)), если n >0, m >0.
*/
ifstream fin("input.txt");
ofstream fout ("output.txt");
int main()
{
    int n;
    int m;
    if(isCorrectInputFile(fin)){
        while(fin >> n >> m){
            fout << AckermannFunction(n, m) << endl;
        }
    }
    system("pause");
    return 0;
}
