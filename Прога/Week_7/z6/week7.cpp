#include "week7.h"
void fPrintLettersDigitsOthers(ofstream& _fout, char * str){
    int amountOfDigits = 0;
	int amountOfLetters = 0;
	int length = strlen(str);
	for(int i = 0; i < length; i++){
		amountOfDigits += isdigit(str[i]);
		amountOfLetters += isalpha(str[i]);
	}
	_fout << "Letters: " << amountOfLetters << " Digits: " << amountOfDigits << " Others: " << length - amountOfDigits - amountOfLetters << endl;
}
char * removeSubStr(char* str, char* word){
    int length = strlen(str);
    int wordSize = strlen(word);
    char* first = strstr(str, word);
    if(first != NULL){
        char *ending = &str[strlen(str)-1];
        while(first + wordSize <= ending){
            *first = *(first+wordSize);
            first++;
        }
        memset(ending - wordSize + 1, 0x00, wordSize);
        removeSubStr(str, word);
    } else {
        return str;
    }
}
int maxAtMatrix(int ** matrix, int n, int m){
    int maxValue = matrix[0][0];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(maxValue < matrix[i][j]){
                maxValue = matrix[i][j];
            }
        }
    }
    return maxValue;
}

int minAtMatrix(int ** matrix, int n, int m){
    int minValue = matrix[0][0];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(minValue > matrix[i][j]){
                minValue = matrix[i][j];
            }
        }
    }
    return minValue;
}
void printTwoLetterCombinations(ofstream& _fout, char * str){
    int length = strlen(str);
    const int ALPHABET_LENGTH = 26;
    int ** twoLetterCombinations = new int*[ALPHABET_LENGTH];
    for(int i = 0; i < ALPHABET_LENGTH; i++){
        twoLetterCombinations[i] = new int[ALPHABET_LENGTH];
        for(int j = 0; j < ALPHABET_LENGTH; j++){
            twoLetterCombinations[i][j] = 0;
        }
    }
    int j = 0;
    for(int i = 0; i < length-1; i++){
        if(isalpha(str[i])){
            j = i;
            break;
        }
    }
    for(int i = j+1; i < length; i++){
        if(isalpha(str[i])){
            twoLetterCombinations[toupper(str[j])-'A'][toupper(str[i])-'A']++;
            j = i;
        }
    }
    int symbols = 0;
    int maxValue = max(abs(maxAtMatrix(twoLetterCombinations, ALPHABET_LENGTH, ALPHABET_LENGTH)),
                       abs(minAtMatrix(twoLetterCombinations, ALPHABET_LENGTH, ALPHABET_LENGTH)));
    while(maxValue > 0){
        maxValue/=10;
        symbols++;
    }
    _fout <<setw(symbols) << ' ' << " ";
    for(int i = 0; i < ALPHABET_LENGTH; i++){
        _fout <<setw(symbols) << (char)(i+'A') <<" ";
    }
    _fout <<endl;
    for(int i = 0; i < ALPHABET_LENGTH; i++){
        _fout <<setw(symbols) << (char)(i+'A') <<" ";
        for(int j = 0; j < ALPHABET_LENGTH; j++){
            _fout <<setw(symbols)<< twoLetterCombinations[i][j] << " ";
        }
        _fout <<endl;
    }
    _fout << endl;
}
void reverseWords(ofstream &_fout, char* str){
    int length = strlen(str);
    int start = 0;
    for(; start < length; start++){
        if(isalpha(str[start])){
           break;
        } else {
            _fout << str[start];
        }
    }
    bool isWordStarted = true;
    if(start < length-1){
        int a = start;
        for(int i = a+1; i < length; i++){
            bool isLetter = isalpha(str[i]);
            if(!isLetter && isWordStarted){
                for(int j = i-1; j >= a;j--){
                    _fout << str[j];
                }
                _fout << str[i];
                isWordStarted = false;
            } else if(!isLetter && !isWordStarted){
                _fout << str[i];
            }else if(isLetter && !isWordStarted){
                a = i;
                isWordStarted = true;
            }
        }
        if(isWordStarted){
            for(int j = length-1; j >= a; j--){
                _fout << str[j];
            }
        }
    } else {
        _fout << str;
    }
     _fout<<endl;
}
int findSubstr(char* str, char*sub){
    int strLength = strlen(str);
    int subLength = strlen(sub);
    bool isBroken = false;
    int i = 0;
    for(; i < strLength- subLength + 1 && !isBroken; i++){
        for(int j = 0; j < subLength; j++){
            if(str[i + j] != sub[j]){
                break;
            } else if(j == subLength - 1){
                isBroken = true;
            }
        }
    }
    return i - 1 - ((int)!isBroken)*(strLength- subLength + 2);
}
void replaceWith(char* &str, char* oldSubstr, char* newSubstr){
    int length = strlen(str);
    int oldSubstrSize = strlen(oldSubstr);
    int newSubstrSize = strlen(newSubstr);
    int delta = newSubstrSize - oldSubstrSize;
    int first = findSubstr(str, oldSubstr);
    if(first > -1){
        int ending = strlen(str)-1 + delta;
        int temp = strlen(str);
        if(delta > 0){
            for(int i = ending; i >= first + oldSubstrSize; i--){
                str[i] = str[i - delta];
            }
        } else {
            for(int i = first + newSubstrSize; i <= ending; i++){
                str[i] = str[i - delta];
            }
        }
        for(int i = 0; i < newSubstrSize; i++){
            str[i + first] = newSubstr[i];
        }
        str[temp + delta] = '\0';
        replaceWith(str, oldSubstr, newSubstr);
    }
}