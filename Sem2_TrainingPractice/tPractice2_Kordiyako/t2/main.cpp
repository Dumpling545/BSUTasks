#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iterator>
#include <set>
#include <map>
using namespace std;
ifstream fin("input.txt");
int main()
{
    vector<string> vect;
    string elem;
    while(fin >> elem){
        vect.push_back(elem);
    }
    sort(vect.begin(), vect.end());
    cout << "Sorted vector: " <<endl;
    for_each(vect.begin(), vect.end(), [cout](string str){ cout << str << " ";});
    cout << endl;
    cout << "Enter symbol: " <<endl;
    char c;
    cin >> c;
    vector<string> startsWith;
    copy_if(vect.begin(), vect.end(),inserter(startsWith, startsWith.begin()), [c] (string str){return str[0] == c;});
    cout << "Words that start with '"<<c<<"':" <<endl;
    for_each(startsWith.begin(), startsWith.end(), [cout](string str){ cout << str << " ";});
    cout << endl << "Enter symbol (words that start with this symbol will be deleted): " <<endl;
    cin >> c;
    std::vector<string>::iterator p1=find_if(vect.begin(), vect.end(), [c](const string & s) {return s[0] == c;});
    std::vector<string>::iterator p2=find_if(p1, vect.end(), [c](const string & s) {return s[0] != c;});
    vect.erase(p1, p2);
    cout << "Result:" <<endl;
    for_each(vect.begin(), vect.end(), [cout](string str){ cout << str << " ";});
    set<string> s_set(vect.begin(), vect.end());
    cout << endl << "Unique words: " <<endl;
    for_each(s_set.begin(), s_set.end(), [cout](string str){ cout << str << " ";});
    cout << endl << "Count unique words: " <<endl;
    map<string, int> unique_map;
    for_each(vect.begin(), vect.end(), [&unique_map](string str){ unique_map[str]++;});
    for_each(unique_map.begin(), unique_map.end(), [cout](pair<string, int> p){ cout << p.first << "(" << p.second <<") ";});
    return 0;
}
