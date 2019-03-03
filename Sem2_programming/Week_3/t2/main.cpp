#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
/**
    Задан файл с текстом на английском языке. Выделить все различные слова.
    Для каждого слова подсчитать частоту его встречаемости.
    Слова, отличающиеся регистром букв, считать различными.
*/
using namespace std;
ofstream fout("output.txt");
ifstream fin("input.txt");
int main()
{
    string str;
    multiset<string> words;
    while(fin >> str){
        str.erase(remove_if(str.begin(),
                             str.end(),
                             [](char ch)
                             { return ch==','||ch=='.'|| ch=='!'; }),
                            str.end());
        words.insert(str);
    }
    int c = 1;
    set<string>::iterator it = words.begin();
    string last = *it;
    fout << last;
    it++;
    while(it!=words.end()){
        if((*it).compare(last) == 0){
            c++;
        } else {
            fout << " (" << c <<")" << endl;
            last = *it;
            fout << last;
            c = 1;
        }
        it++;
    }
    fout << " (" << c <<")" << endl;
    return 0;
}
