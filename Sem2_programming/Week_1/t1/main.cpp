#include <iostream>
#include "vector.h"
#include "charvectormanager.h"
/**
    �������� vector<char>, ���������� ����� � ���������� �������.
    ������������ �������� ����� ������� � ������ � �������� ��������.
*/
using namespace std;

int main()
{
    Vector<char> vect;
    for(char c = 'a'; c <= 'z'; c++){
        vect.push_back(c);
    }
    CharVectorManager manager(&vect);
    manager.print();
    manager.printReverse();
    return 0;
}
