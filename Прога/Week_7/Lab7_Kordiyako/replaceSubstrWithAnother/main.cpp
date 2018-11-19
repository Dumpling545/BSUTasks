#include "week7.h"
using namespace std;
/**
        В данной строке все вхождения подстроки str1 заменить подстрокой str2
*/
ifstream fin("input.txt");
ofstream fout("output.txt");
int main()
{
    int n = 1000;
    char * str = new char[n];
    char oldSub[n];
    char newSub[n];
    while(fin.getline(str, n)){
        fin.getline(oldSub, n);
        fin.getline(newSub, n);
        replaceWith(str, oldSub, newSub);
        fout << str << endl;
    }
    system("pause");
    return 0;
}
