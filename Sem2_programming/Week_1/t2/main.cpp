#include "stringlistmanager.h"
#include <iostream>
#include <fstream>
/**
    �������� list<string>, �������� � ���� ������ ���� �� ���������� �����. ���������:
    -	���������� ������;
    -	������ ���������������� ������;
    -	������ ��������� ������, ������������ �� �������� �����
    -	�������� ��������� ������ �� �������� �����;
    -	������ ������ ����� �������� ���������.
*/
using namespace std;
ifstream fin("input.txt");
int main()
{
    list<string> li;
    string s;
    while(fin >> s){
        li.push_back(s);
    }
    li.sort();
    StringListManager slmanager(&li);
    slmanager.print();
    slmanager.printElementsStartWith('d');
    slmanager.deleteElementsStartWith('d');
    slmanager.print();
    return 0;
}
