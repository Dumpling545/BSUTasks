#include "practice4.h"
using namespace std;

/** Дан двумерный массив (n x m). Найти:
а) число пар одинаковых соседних элементов в каждой строке;
б) число пар одинаковых соседних элементов в каждом столбце.

*/
ofstream fout("output.txt");
ifstream fin ("input.txt");

int main()
{
    int n, m;
    while(fin >> n >> m){
        if(n > 0 && m > 0){
            int ** matrix = fCreateMatrix(fin, n, m);
            fout << "Horizontal pairs: " << countRowPairsMatrix(matrix, n, m) << ", Vertical pairs: " << countColumnPairsMatrix(matrix, n, m) <<endl;
            fout << endl;
        }
    }
    system("pause");
    return 0;
}
