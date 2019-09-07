#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include "stack.h"
#include "week9.h"
using namespace std;
/**
    (5 баллов) Дана строка, которая представляет собой исходное математическое выражение,
    содержащее целые числа, операции +,  *, -, /  и скобки любой степени вложенности.
    Перевести его в обратную польскую запись и вычислить значение записанного выражения.
*/
ofstream fout("output.txt");
ifstream fin ("input.txt");

int main()
{
    const int N = 1000;
    char * str = new char[N];
    if(isCorrectInputFile(fin)){
        while(fin.getline(str,N)){
            fout << computeString(str) << endl;
        }
    }
    return 0;
}
