#pragma once
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
void lettersContains(ofstream fout, char * word1, char *word2, bool withRepeats = true);
char * getUniqueLetters(char * str);
struct Word{
    char * name;
    int counter;
};
Word * getWordsCount(char * str, int &m);
char * stringDivideSentences(char * &str, const char * delims);
char * findWordInAllSentences( char * str);