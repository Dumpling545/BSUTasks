#include "practice4.h"
using namespace std;

/**»спользу€ датчик случайных чисел, заполнись двумерный массив (n x m) неповтор€ющимис€ числами.
*/
ofstream fout("output.txt");
ifstream fin ("input.txt");


int main()
{
    int n, m;
    while(fin >> n >> m){
        if(n > 0 && m > 0){
            int ** matrix = createMatrix(n, m);
            fillMatrixUniqueNumbers(matrix, n, m);
            fPrintMatrix(fout, matrix, n,m);
        }
    }
    system("pause");
    return 0;
}
