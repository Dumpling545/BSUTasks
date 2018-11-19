#include <iostream>
#include <cstring>
#include "stack.h"
#include "week9.h"
using namespace std;
/**
    (4 балла) Пусть дана без ошибок формула, имеющая следующий синтаксис:
    <формула>::=<цифра> | max(<формула>, < формула >) | min (<формула>,< формула >)
    <цифра>::=0  1  2  3  4  5  6  7  8   9
    Например, 8 или max(4, min(3, 5)) или  min(min(3, 5), max(2, max(3, 4))).
*/
ofstream fout("output.txt");
ifstream fin ("input.txt");

int main()
{
    const int N = 1000;
    char * str = new char[N];
    if(isCorrectInputFile(fin)){
        while(fin.getline(str,N)){
            fout << computeMinMaxString(str) << endl;
        }
    }
    return 0;
}
