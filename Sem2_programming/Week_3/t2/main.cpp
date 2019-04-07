#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <utility>
#include <map>
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
void fillVectorWithWords(vector<string>& vect, istream& is){
    string str;
    while(is >> str){
        str.erase(remove_if(str.begin(),
                             str.end(),
                             [](char ch)
                             { return ch==','||ch=='.'|| ch=='!' || ch=='?'; }),
                            str.end());
        vect.push_back(str);
    }
}
map<string, int> getUniqueWords(vector<string> words){
    sort(words.begin(), words.end());
    map<string, int> result;
    vector<string>::iterator it = words.begin();
    string last = *it;
    int counter = 1;
    it++;
    while(it!=words.end()){
        map<string, int>::iterator elemFound = result.find(*it);
        if(elemFound == result.end()){
            result[*it] = 1;
        } else {
            (*elemFound).second++;
        }
        it++;
    }
    return result;
}
void printWords(map<string,int> words, ostream& os){
    map<string, int>::iterator it = words.begin();
    while(it != words.end()){
        os << (*it).first << "(" <<(*it).second <<")" <<endl;
        it++;
    }
}
int main()
{
    if(isCorrectInputFile(fin)){
        vector<string> words;
        fillVectorWithWords(words, fin);
        map<string,int> uniqueWords = getUniqueWords(words);
        printWords(uniqueWords, fout);
    }
    return 0;
}
