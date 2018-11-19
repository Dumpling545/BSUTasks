#include <iostream>
#include <fstream>
#include <cstring>
#include "week9.h"
using namespace std;
/** ���� �������������� ��������� � ���� ������ ��������.
    �������� ���������, ������� ���������, ��������� �� ����������� ������ � ���������,
    ���� ��� ������� �� ������ ����: ( ) [ ] { }. (������������ ��������� ������ ����).
*/
ofstream fout("output.txt");
ifstream fin("input.txt");

int main()
{
    const int N = 1000;
    char * str = new char[N];
    if(isCorrectInputFile(fin)){
        while(fin.getline(str,N)){
            if(isCorrectBrackets(str)){
                fout << "Brackets are correct" <<endl;
            } else {
                fout << "Brackets are incorrect" <<endl;
            }
        }
    }
    return 0;
}
