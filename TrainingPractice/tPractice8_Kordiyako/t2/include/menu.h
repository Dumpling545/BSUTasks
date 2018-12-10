/**
�������� ���������, ��������������� ������ � ���� �������.
��������� ������ ��������� ����, ����������� ����������� �������� ���� ������� ������.
�������� ������ 1-�� �  2-�� ��������� ��������� �� ������. ��������� �������� ���������� � �������� ����.
���������� � �������� ��������� ����������� � ����������.

*/
#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include "validator.h"
#include "set.h"
class Menu
{
    public:
        const static int LOAD = 0;
        const static int UNION = 1;
        const static int INTERSECTION = 2;
        const static int DIFFERENCE = 3;
        const static int EQUALITY = 4;
        const static int FIRST_INCLUDES_SECOND = 5;
        const static int SECOND_INCLUDE_FIRST = 6;
        const static int ADD = 7;
        const static int REMOVE = 8;
        const static int PRINT_SET = 9;
        Menu();
        void printHint();
        void startInput();
        void handleCommand(int command);
    private:
        bool isInit = false;
        Set s1;
        Set s2;
};
