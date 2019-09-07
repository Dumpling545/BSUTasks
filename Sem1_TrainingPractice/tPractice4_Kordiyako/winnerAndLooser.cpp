#include "practice4.h"
using namespace std;

/**
        � ��������� ������� �������� n x n �������� ���������� �����,
        ��������� ��� ��� ���� �������� �� �������� � ������� ���������
        (3 � ���� ������ ������� �������� ����, 0 � ���� ���������, 1 � ���� ���� ����������� ������).
        ����������:
        �) ������� ����� ������� �������, ������� ���������,
        �) ����� �������, �������� ��������� �����.
*/
ofstream fout("output.txt");
ifstream fin ("input.txt");

int main()
{
    int n, m;
    while(fin >> n){
        if(n > 1){
            int ** matrix = fCreateMatrix(fin, n, n);
            fout << "Winner: �" << maxRowIndex(matrix, n)+1 << ", looser: �" <<minRowIndex(matrix, n)+1 <<endl;
            fout << endl;
        }
    }
    system("pause");
    return 0;
}
