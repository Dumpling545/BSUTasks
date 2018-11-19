#include "practice5.h"
using namespace std;
/**
    Даны два слова. Для каждой буквы первого слова (а) в том числе для повторяющихся в этом слове букв;
    б) повторяющиеся буквы первого слова не рассматривать) определить, входит ли она во второе слово.
    Например, если заданные слова процессор и информация, то для букв первого из них ответом должно быть:
    а) нет да да да нет нет нет нет нет, б) нет да да да нет нет.
*/
ofstream fout("output.txt");
ifstream fin("input.txt");
int main()
{
    int n = 1000;
    char * word1 = new char[n];
    char * word2 = new char[n];
    while(fin>>word1>>word2){
        lettersContains(fout, word1, word2);
        lettersContains(fout, word1, word2, false);
    }
    return 0;
}
