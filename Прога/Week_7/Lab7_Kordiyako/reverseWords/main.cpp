#include "week7.h"
using namespace std;
/**
        Дана строка. «Перевернуть» в строке все слова
        (например: «Жили были дед и баба» - «илиЖ илыб дед и абаб»). Зам. Исходную строку не менять
*/
ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
    int n = 1000;
    char str[n];
    while(fin.getline(str, n)){
        reverseWords(fout, str);
        delete [] str;
    }
    system("pause");
    return 0;
}
