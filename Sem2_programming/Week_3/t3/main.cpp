#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>
/**
    Самостоятельно реализовать лексикографическую
    сортировку с использованием множества и очереди
    (см. файл lexicographicalSorting)
*/
using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");
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
void lexicographicalSort(vector<string> & words){
    int max_length = 0;
    for(int i = 0; i < words.size(); i++){
        if(max_length < words[i].length()) max_length = words[i].length();
    }
    vector<queue<string>> by_length(max_length);
    for(int i = 0; i < words.size(); i++){
        by_length[words[i].length() - 1].push(words[i]);
    }
    words.clear();
    map<char, queue<string>> by_alphabet;
    for(int i = max_length-1; i >= 0; i--){
        while(!by_length[i].empty()){
            by_alphabet[by_length[i].front()[i]].push(by_length[i].front());
            by_length[i].pop();
        }
        for(int t = 0; t < words.size(); t++){
            by_alphabet[words[t][i]].push(words[t]);
        }
        words.clear();
        for(char symbol = 'a'; symbol <= 'z'; symbol++){
            while(!by_alphabet[symbol].empty()){
                words.push_back(by_alphabet[symbol].front());
                by_alphabet[symbol].pop();
            }
        }
    }
}

int main(){
    if(isCorrectInputFile(fin)){
        int max_length = 0;
        vector<string> words;
        string str;
        while(fin >> str){
            words.push_back(str);
        }
        lexicographicalSort(words);
        for(int index = 0; index < words.size(); index++){
            fout << words[index] << endl;
        }
    }
    return 0;
}
