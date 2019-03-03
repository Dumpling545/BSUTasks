#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
/**
    Самостоятельно реализовать лексикографическую
    сортировку с использованием множества и очереди
    (см. файл lexicographicalSorting)
*/
using namespace std;
ifstream fin("input.txt");
ifstream fout("output.txt");
int main()
{
    vector<vector<string>> by_length(100);
    string str;
    int max_len = 1;
    while(fin >> str){
        if(max_len < str.length()) max_len = str.length();
        by_length[str.length()].push_back(str);
    }
    vector<string> result;
    map<char, vector<string>> by_alphabet;
    for(int i = max_len; i >=1; i--){
        for(int j = 0; j < by_length[i].size(); j++){
            by_alphabet[by_length[i][j][i-1]].push_back(by_length[i][j]);
        }
        for(int t = 0; t < result.size(); t++){
            by_alphabet[result[t][i-1]].push_back(result[t]);
        }
        result.clear();
        for(char c = 'a'; c <= 'z'; c++){
            if(!by_alphabet[c].empty()){
                for(int k = 0; k < by_alphabet[c].size(); k++){
                    result.push_back(by_alphabet[c][k]);
                }
            }
        }
        by_alphabet.clear();
    }
    for(int index = 0; index < result.size(); index++){
        cout << result[index] << endl;
    }
    return 0;
}
