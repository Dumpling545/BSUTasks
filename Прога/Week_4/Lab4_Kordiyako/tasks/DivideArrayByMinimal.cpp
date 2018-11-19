#include <iostream>
#include "arrays.h"
#include "lab4.h"
using namespace std;
/**
    ��� ������ ����� �����. ����������� ������� ��� ��������� ������� ����� �����.
    ������� ������� ����������� ������� ������� � ��������� ��� �������� ����� ��� �� ��������,
    � ������ ��� � �� �����������. ������� ���������� ������ ������������ ��������.

    Input                                   Output
    -------------------------------------------------------------------
    -1                                      Incorrect natural number. Re-enter:

    10                                      8 7 4 3 2 0 1 5 6 9
    2 8 3 7 4 0 1 9 5 6                     5

    10                                      9 8 7 6 5 4 3 2 1 0
    2 8 3 7 4 1 9 5 6 0                     9

    10                                      0 1 2 3 4 5 6 7 8 9
    0 2 8 3 7 4 1 9 5 6                     0

*/

int main()
{
    int n;
    cout << "Enter n:" << endl;
    enterNatural(n);
    int *ar = enterArray(n);
    cout << SortByMinimum(ar, n) << endl;
    system("pause");
    return 0;
}
