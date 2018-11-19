#include "practice4.h"

using namespace std;

/** ƒан двумерный массив ненулевых целых чисел (n x m). ќпределить, сколько раз элементы массива мен€ют знак
(принима€, что массив просматриваетс€ построчно сверху вниз, а в каждой строке Ц слева направо).
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
