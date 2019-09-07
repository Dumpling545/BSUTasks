#include <iostream>
#include <queue>
#include <iomanip>
#include <string>
#include <time.h>
#include "arrays.h"
#include "week5.h"
using namespace std;
/**
    Двумерная матрица задает высоты соседствующих клеток местности.
    Переход возможен в соседние клетки по горизонтали или по вертикали,
    если высота соседа меньше (как стекает вода).
    1)Определить все клетки, в которые можно попасть из заданной.

    2)Определить самую удаленную клетку, в которую можно попасть из заданной.

    3)Найти путь для подзадачи 2.


    Используйте поиск в ширину для решения задачи.

    Для тестирования подготовить достаточно большие матрицы.
    При выводе показывать матрицу исходную и матрицу с результирующим путем (выделяя его, например, каким-то символом).

    Input                       Output
    ---------------------------------------------------------------------------
    10 10                       54 43 24 22 81 14  6 78 95 58
    2 2                         29 78 87 22 87 64 21 31 44 16
                                27 85 56  4 13 19  7 26 73 59
                                27  2 51 41 61 72 72 74 42 94
                                86 12 67 29 40 48 46 10 69 23
                                79 51 82 89 47 83 55 31 52 62
                                19 90 14 68 25  5  1 21 65 68
                                62  1  7 69 38 73 72 39 72 49
                                62 40 90 67 39 91  7  0 65 99
                                91 39 44 51 88 31 11 18 96 12
                                X X X X X X X X X X
                                X X X X X X X X X X
                                X X S @ X X X X X X
                                X @ @ @ X X X X X X
                                X X X D X X X X X X
                                X X X X X X X X X X
                                X X X X X X X X X X
                                X X X X X X X X X X
                                X X X X X X X X X X
                                X X X X X X X X X X

*/

int main()
{
    srand(time(NULL));
    int n;
    enterNatural(n, "n");
    int m;
    enterNatural(m, "m");
    int **matrix = createMatrix(n,m);
    cout <<endl;
    fillMatrixWithRandomValues(matrix,n,m);
    cout <<endl;
    int x0;
    enterInteger(x0, "x0",matchMatrix);
    while(x0 >= n){
        cout << "Out of range" <<endl;
        enterInteger(x0, "x0",matchMatrix);
    }
    cout <<endl;
    int y0;
    enterInteger(y0, "y0", matchMatrix);
    while(y0 >= n){
        cout << "Out of range" <<endl;
        enterInteger(y0, "y0",matchMatrix);
    }
    cout <<endl;
    cout << "Cells which you can reach from S("<<x0 <<", " << y0 <<") are marked by '@', " <<
    "most distant element (but not starting) is marked by 'D'(others - X):" << endl;
    int ** bfs = BFS(matrix,n,m,x0,y0,CanGo);
    bool** can = canReach(bfs, n, m, x0, y0);
    pair<int, int> mde = mostDistantElement(bfs, n, m, x0, y0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(i == x0 && j == y0){
                cout <<"S ";
            } else if(i == mde.first && j == mde.second){
                cout <<"D ";
            } else if(can[i][j]){
                cout << "@ ";
            } else {
                cout <<"X ";
            }
        }
        cout<<endl;
    }
    system("pause");
    return 0;
}
