#include "week7.h"
/**���� ������. ��������� � ��� ������� ���� �������������
��������� ��� ����� �������� � ��� ����� ��������, �� ���������� �������.
*/
using namespace std;
ofstream fout("output.txt");
ifstream fin ("input.txt");

int main()
{
    int n = 1000;
    char str[n];
    while(fin.getline(str, n)){
        printTwoLetterCombinations(fout, str);
        delete [] str;
    }
    system("pause");
    return 0;
}
