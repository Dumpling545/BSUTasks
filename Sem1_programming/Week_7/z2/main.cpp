#include "week7.h"
using namespace std;
/**
        Удалить из строки заданное слово
*/
ifstream fin("input.txt");
ofstream fout("output.txt");
int main()
{
    int n = 1000;
    char str[n];
    char word[n];
    while(fin.getline(str, n)){
        fin.getline(word, n);
        int length = strlen(str);
        int wordSize = strlen(word);
        fout << removeSubStr(str, word) <<endl;
        delete [] word;
        delete [] str;
    }
    system("pause");
    return 0;
}
