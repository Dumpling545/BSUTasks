#include <iostream>
#include "rational.h"
using namespace std;
/**
    (5 ������) ������������ (������������) ����� �������������� ����� ����� ����� (a,b),
    ��� a � ���������, b � �����������. ������� ����� Rational ��� ������ � ������������� �������.
    ����������� ������������: ����������� � �������������, � ����� ������:
    �������� add, (a,b) + (c,d) = (ad+bc,bd);
    ��������� mul, (a,b) * (c,d) = (ac, bd);
    ������� div, (a,b)/(c,d) = (ad,bc);
    ��������� equal, greater, less;
    ����� print.
    ���. ����������� ��������� ������� ���������� ����� reduce, ������� �����������
    ���������� ��� ���������� �������������� ��������.
*/
int main()
{
    Rational r1(-3003,2210);
    Rational r2(-1,-3);
    r1.print(cout);
    cout << " + ";
    r2.print(cout);
    cout << " = ";
    (r1 + r2).print(cout);
    cout << endl;
    r1.print(cout);
    cout << " - ";
    r2.print(cout);
    cout << " = ";
    (r1 - r2).print(cout);
    cout << endl;
    r1.print(cout);
    cout << " * ";
    r2.print(cout);
    cout << " = ";
    (r1 * r2).print(cout);
    cout << endl;
    r1.print(cout);
    cout << " / ";
    r2.print(cout);
    cout << " = ";
    (r1 / r2).print(cout);
    cout << endl;
    if(r1 > r2){
        r1.print(cout);
        cout << " > ";
        r2.print(cout);
    } else if(r1 < r2){
        r1.print(cout);
        cout << " < ";
        r2.print(cout);
    } else {
        r1.print(cout);
        cout << " == ";
        r2.print(cout);
    }
    return 0;
}
