#include <fstream>
#include "practice6.h"
#include <limits>
/**
    Написать рекурсивную функцию, определяющую,
    является ли симметричной часть строки s, начиная с i-го элемента и кончая j-м.
*/

using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");
int main()
{
    const int DEF_SIZE = 1000;
    int i;
    int j;
    char *str = new char[DEF_SIZE];
    if(isCorrectInputFile(fin)){
        while(fin >> i >> j){
            fin.getline(str, DEF_SIZE);
            fin.getline(str, DEF_SIZE);
            fout << "Substring("<<i<<", " <<j<<") is ";
            if(!isPalindrome(str, i, j)){
                fout << "not ";
            }
            fout << "a palindrome" << endl;
            delete [] str;
            str = new char[DEF_SIZE];
        }
    }
    system("pause");
    return 0;
}
