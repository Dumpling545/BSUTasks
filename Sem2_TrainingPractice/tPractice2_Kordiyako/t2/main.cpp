#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iterator>
#include <set>
#include <map>
#include "include/practice2.h"
using namespace std;
ifstream fin("input.txt");
int main()
{
    if(isCorrectInputFile(fin)){
        vector<string> vect;
        string elem;
        fillVector<string>(fin, vect);
        sort(vect.begin(), vect.end());
        cout << "Sorted vector: " <<endl;
        printInterval<string>(vect.begin(), vect.end());
        char c;
        enterElement<char>(c, "symbol");
        vector<string> startsWith;
        getWordsStartWith(startsWith, vect, c);
        cout << "Words that start with '"<<c<<"':" <<endl;
        printInterval<string>(startsWith.begin(), startsWith.end());
        cout << "Deleting elements started with s: " <<endl;
        enterElement<char>(c, "s (symbol)");
        deleteWordsStartWith(vect, c);
        cout << "Result:" <<endl;
        printInterval<string>(vect.begin(), vect.end());
        set<string> s_set(vect.begin(), vect.end());
        cout << "Unique words: " <<endl;
        printInterval<string>(s_set.begin(), s_set.end());
        cout << endl << "Count word repeats: " <<endl;
        map<string, int> unique_map;
        countWordRepeats(unique_map, vect);
        for_each(unique_map.begin(), unique_map.end(), [cout](pair<string, int> p){
                  cout << p.first << "(" << p.second <<") ";
                  });
    }
    return 0;
}
