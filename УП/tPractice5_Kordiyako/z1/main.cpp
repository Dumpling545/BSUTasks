#include "practice5.h"
using namespace std;
/**
    ���� ��� �����. ��� ������ ����� ������� ����� (�) � ��� ����� ��� ������������� � ���� ����� ����;
    �) ������������� ����� ������� ����� �� �������������) ����������, ������ �� ��� �� ������ �����.
    ��������, ���� �������� ����� ��������� � ����������, �� ��� ���� ������� �� ��� ������� ������ ����:
    �) ��� �� �� �� ��� ��� ��� ��� ���, �) ��� �� �� �� ��� ���.
*/
ofstream fout("output.txt");
ifstream fin("input.txt");
int main()
{
    int n = 1000;
    char * word1 = new char[n];
    char * word2 = new char[n];
    while(fin>>word1>>word2){
        lettersContains(fout, word1, word2);
        lettersContains(fout, word1, word2, false);
    }
    return 0;
}
