#include "week7.h"
using namespace std;
/**
        ���� ������. ������������� � ������ ��� �����
        (��������: ����� ���� ��� � ���� - ����� ���� ��� � ����). ���. �������� ������ �� ������
*/
ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
    int n = 1000;
    char str[n];
    while(fin.getline(str, n)){
        reverseWords(fout, str);
        delete [] str;
    }
    system("pause");
    return 0;
}
