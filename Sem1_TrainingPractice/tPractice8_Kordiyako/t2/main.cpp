#include <iostream>
#include "menu.h"
using namespace std;
/**
    2. ������� ����� ���������� �� ���������- �������� (��������� �� ��� char;
    ���������� ��������� � ������ ���������  -  �� ����� 256).
���������� � ����������� � ������ ������������,  ����������, �����������   �������� ������������ �  <<   >>.
��������� ����������� ������ ��������� �������������� ����������
(*- �����������, + -�����������, - -��������, < - ���������, = = - ��������������� )  .
����������� ��� ��������, � ����� ��������  ���������� � �������� ��������, ��������� ������������.
�������� ���������, ��������������� ������ � ���� �������.
��������� ������ ��������� ����, ����������� ����������� �������� ���� ������� ������.
�������� ������ 1-�� �  2-�� ��������� ��������� �� ������. ��������� �������� ���������� � �������� ����.
���������� � �������� ��������� ����������� � ����������.

*/
int main()
{
    Menu menu;
    menu.printHint();
    menu.startInput();
    return 0;
}
