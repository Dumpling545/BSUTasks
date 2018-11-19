#include "week7.h"
using namespace std;
/**
    Дан код программы на С++.Вывести построчно все операции и частоту их использования в программе.
*/
ifstream fin("input.txt");
ofstream fout("output.txt");
int main()
{
    int n = 1000;
    char str[n];
    const int OPERATORS_NUMBER = 34;
    char  * operators[OPERATORS_NUMBER] = { "++", "--", "<=", ">=", "==", "!=", "||", "&&", "+=", "-=",
     "*=", "/=", "%=", "&=", "^=" , "|=", "<<", ">>", "(", "[", "+", "-", "*", "/", "%", "*",
     "&","|", "^","<", ">", ".", ",", "="};
    long counter[OPERATORS_NUMBER];
    for(int i = 0; i < OPERATORS_NUMBER; i++){
        counter[i] = 0;
    }
    while(fin.getline(str, n)){
        for(int i = 0; i < OPERATORS_NUMBER; i++){
            int startlength = strlen(str);
            removeSubStr(str, operators[i]);
            counter[i] += (startlength - strlen(str))/strlen(operators[i]);
        }
        delete [] str;
    }
    for(int i = 0; i < OPERATORS_NUMBER; i++){
        fout << "Operator: " << operators[i] << "  " <<counter[i] <<endl;
    }
    system("pause");
    return 0;
}
