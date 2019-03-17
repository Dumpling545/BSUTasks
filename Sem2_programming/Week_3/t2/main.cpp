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

bool isCorrectInputFile(ifstream &_fin){
    bool res = true;
    if(!_fin){
        cout << "Input file doesn't exist" << endl;
        res =  false;
    } else if(_fin.peek() == ifstream::traits_type::eof()){
        cout << "Input file is empty" << endl;
        res = false;
    }
    return res;
}
void printUniqueWords(){
    string str;
    multiset<string> words;
    while(fin >> str){
        str.erase(remove_if(str.begin(),
                             str.end(),
                             [](char ch)
                             { return ch==','||ch=='.'|| ch=='!' || ch=='?'; }),
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
}

int main()
{
    if(isCorrectInputFile(fin)){
        printUniqueWords();
    }
    return 0;
}
