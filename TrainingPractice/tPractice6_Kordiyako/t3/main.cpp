#include <iostream>
#include <fstream>
#include "practice6.h"
/**
    �������� ����������� ������� ���������� ��������� ����� ������������ �����.
    �������� ������ ������� ����� ���������� ��������� �������:
    ���� ������� ��� ����� ����� �����, ����� ��� ����� ��������� ����� � ��������� ���� �������,
    �� � ���������� ����� �������� ����������� ����� (�����),
    ������� � ���������� �������� ������ ������� �����. ��������: 15 634 -> 19 ->10 -> 1
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
