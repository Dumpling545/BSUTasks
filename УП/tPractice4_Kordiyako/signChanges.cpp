#include "practice4.h"

using namespace std;

/** ��� ��������� ������ ��������� ����� ����� (n x m). ����������, ������� ��� �������� ������� ������ ����
(��������, ��� ������ ��������������� ��������� ������ ����, � � ������ ������ � ����� �������).
*/
ofstream fout("output.txt");
ifstream fin ("input.txt");
int main()
{
    int n, m;
    while(fin >> n >> m){
        if(n > 0 && m > 0){
            int ** matrix = fCreateMatrix(fin, n, m);
            fout << countSignChangesMatrix(matrix,n,m)<<endl;
            fout << endl;
        }
    }
    system("pause");
    return 0;
}
