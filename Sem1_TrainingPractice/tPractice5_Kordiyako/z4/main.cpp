#include "practice5.h"
using namespace std;
/**
     Дан текст, состоящий из предложений. Найти слово, которое встречается во всех предложениях текста, или сообщить, что такого слова нет.
*/
ofstream fout("output.txt");
ifstream fin("input.txt");
int main()
{
    int n = 1000;

    char * str = new char[n];
    while(fin.getline(str, n)){
        int m = 0;
        fout << findWordInAllSentences(str) <<endl;
    }
    return 0;
}
