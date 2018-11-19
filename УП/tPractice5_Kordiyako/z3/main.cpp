#include "practice5.h"
using namespace std;
/**
    Дан текст. Посчитать частоту слов в тексте.
*/
ofstream fout("output.txt");
ifstream fin("input.txt");

int main()
{
    int n = 1000;

    char * str = new char[n];
    while(fin.getline(str, n)){
        int m = 0;
        Word* words = getWordsCount(str, m);
        for(int i =0; i < m;i++){
            fout << words[i].name << ": " << words[i].counter << " times" <<endl;
        }
        fout << endl;
    }
    return 0;
}
