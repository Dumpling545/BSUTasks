#include "practice5.h"
using namespace std;
/**
     ��� �����, ��������� �� �����������. ����� �����, ������� ����������� �� ���� ������������ ������, ��� ��������, ��� ������ ����� ���.
*/
ofstream fout("output.txt");
ifstream fin("input.txt");
int main()
{
    int n = 1000;

    char * str = new char[n];
    while(fin.getline(str, n)){
        int m = 0;
        fout << findWordInAllSentences(str) <<endl;
    }
    return 0;
}
