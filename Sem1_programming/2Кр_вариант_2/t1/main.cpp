#include<iostream>
#include<fstream>
#include <cstdlib>
#include <cstring>
#include "polynomial.h"
#include "queue.h"
#include "vector.h"
#include "header.h"
using namespace std;
/**
1. ����������� ������ ������ Queue.

2. ����������� ������ ������ ���������� � Polynom ������� n .
�������� ��������� �������������, � ��� ����� ����������� �����������.
����������� ������ ��� ���������� �������� ��������; ��������, ���������.
����������� �������� ��������, ���������, ��������������, ������������.

3. ��������� ������������ ���������� ��������� �� �����.
������� ������� �������� ������. �������� ��� � �������,
����������� ����� ��������� �������, ������� 3 � ������������
�������-���������, ������� ��������� �� ����� � �������� ���������.
*/
ifstream fin("input.txt");
ofstream fout("output.txt");
int main()
{
    if(isCorrectInputFile(fin)){
        Queue<Polynomial<int>> q;
        char * temp;
        while(fin.getline(temp, 1000)){
            Vector<int> v;
            char * token = strtok (temp," ");
            while (token != NULL)
            {
                v.push_back((int)atoi(token));
                token = strtok (NULL, " ");
            }
            q.push(Polynomial<int>(v, 0));
        }
        Polynomial<int> poly = computePolynomials<int>(q);
        poly.setArgument(0);
        fout << poly.calculate() << endl;
    }
    return 0;
}
