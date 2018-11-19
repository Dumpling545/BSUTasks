#include "week7.h"
using namespace std;
/**
     Дана строка символов. Определить количество букв, количество цифр и количество остальных символов,
    присутствующих в строке.
    Input                                   Output
    -------------------------------------------------------------------------
    *&@#$%^&A1sybc!23$$4,./[5De             Letters: 12 Digits: 5 Others: 10
    ^^^^^^^^^^^^^^^^^^^^^!!!!!!!!!!         Letters: 0 Digits: 0 Others: 32
    1'2/3+==4_-_5*()))67$#8!@9%:            Letters: 0 Digits: 9 Others: 19
    A!b@#C$%^&d*()_+{}:E                    Letters: 7 Digits: 0 Others: 13





*/
ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
    int n= 1000;
    char str[n];
    while(fin.getline(str, n)){
        fPrintLettersDigitsOthers(fout, str);
        delete [] str;
    }
    return 0;
}
