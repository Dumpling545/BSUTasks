#include <iostream>
#include "week5.h"

using namespace std;
/**
    �������� �������, ������� ���������� �������� ����� ����� ���������� ������ �������� � ������������� �������
    � ���������� ��������� �� ����� ��������� ������ ��������. � ������� ������ ������� ����������� ���������� ���������.

    Input                       Output
    ------------------------------------------------------------------
    -1                          Incorrect natural number. Re-enter:

    5                           1 2 3 3 4
    1 4 3 2 3

    10                          -5 -4 -3 -2 -1 1 2 3 4 5
    -5 5 -4 4 -1 1 -2 2 3 -3
*/
int main()
{
    int n;
    enterNatural(n);
    int *ar = new int[n];
    ar = enterArray(n);
    insertionSort(ar, n);
    printArray(ar, n);
    return 0;
}
