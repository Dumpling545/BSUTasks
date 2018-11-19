#include <iostream>
#include <fstream>
#include "practice6.h"
/**
    Написать рекурсивную функцию нахождения цифрового корня натурального числа.
    Цифровой корень данного числа получается следующим образом:
    если сложить все цифры этого числа, затем все цифры найденной суммы и повторять этот процесс,
    то в результате будет получено однозначное число (цифра),
    которая и называется цифровым корнем данного числа. Например: 15 634 -> 19 ->10 -> 1
*/
using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");
int main()
{
    int n;
    if(isCorrectInputFile(fin)){
        while(fin >> n){
            fout << digitalRoot(n)<< endl;
        }
    }
    system("pause");
    return 0;
}
