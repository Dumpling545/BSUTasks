#include "practice4.h"
using namespace std;

/**Дан двумерный массив (n x m). Определить количество различных элементов в нем.
*/
ofstream fout("output.txt");
ifstream fin ("input.txt");

int main()
{
    int n, m;
    while(fin >> n >> m){
        if(n > 0 && m > 0){
            int ** matrix = fCreateMatrix(fin, n, m);
            fout << countUniqueMatrix(matrix, n, m)<<endl;
            fout << endl;
        }
    }
    system("pause");
    return 0;
}
