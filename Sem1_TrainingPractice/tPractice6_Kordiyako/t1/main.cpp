#include <fstream>
#include <iostream>
#include "practice6.h"
using namespace std;
/**Написать рекурсивную функцию для вычисления индекса максимального элемента массива из n элементов.
*/
ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
    int n;
    int* ar;
    if(isCorrectInputFile(fin)){
        while(fin >> n){
            if(n > 0){
                delete [] ar;
                ar = new int[n];
                for(int i = 0; i < n; i++){
                    fin >> ar[i];
                }
                fout << ar[maxElemIndex(ar, n)] << endl;
            } else{
                break;
            }
        }
    }
    system("pause");
    return 0;
}
