#include "practice5.h"
using namespace std;
/**
    ��� �����. � �������� ���� �������� ������ �� ����� ����, ������� ����������� � ������ ������ ������ ���� ���.
    ��������, ��� ������ ��������� ����������, �� ������� ������ ����: � � � � � �.
*/
ofstream fout("output.txt");
ifstream fin("input.txt");
int main()
{
    int n = 1000;
    char * str = new char[n];
    while(fin.getline(str, n)){
        int length = strlen(str);
        char * res = getUniqueLetters(str);
        int lengthResult = strlen(res);
        for(int i = 0; i < lengthResult; i++){
            fout << res[i] << " ";
        }
        fout << endl;
    }
    return 0;
}
