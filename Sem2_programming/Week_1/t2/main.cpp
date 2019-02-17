#include "stringlistmanager.h"
#include <iostream>
#include <fstream>
/**
    Создайте list<string>, считайте в него список слов из текстового файла. Выполните:
    -	сортировку списка;
    -	печать отсортированного списка;
    -	печать элементов списка, начинающихся на заданную букву
    -	удаление элементов списка на заданную букву;
    -	печать списка после удаления элементов.
*/
using namespace std;
ifstream fin("input.txt");
int main()
{
    list<string> li;
    string s;
    while(fin >> s){
        li.push_back(s);
    }
    li.sort();
    StringListManager slmanager(&li);
    slmanager.print();
    slmanager.printElementsStartWith('d');
    slmanager.deleteElementsStartWith('d');
    slmanager.print();
    return 0;
}
