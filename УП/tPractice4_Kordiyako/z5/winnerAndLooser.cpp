#include "practice4.h"
using namespace std;

/**
        В двумерном массиве размером n x n записано количество очков,
        набранных той или иной командой во встречах с другими командами
        (3 – если данная команда выиграла игру, 0 – если проиграла, 1 – если игра закончилась вничью).
        Определить:
        а) сколько очков набрала команда, ставшая чемпионом,
        б) номер команды, занявшей последнее место.
*/
ofstream fout("output.txt");
ifstream fin ("input.txt");

int main()
{
    int n, m;
    while(fin >> n){
        if(n > 1){
            int ** matrix = fCreateMatrix(fin, n, n);
            fout << "Winner: №" << maxRowIndex(matrix, n)+1 << ", looser: №" <<minRowIndex(matrix, n)+1 <<endl;
            fout << endl;
        }
    }
    system("pause");
    return 0;
}
