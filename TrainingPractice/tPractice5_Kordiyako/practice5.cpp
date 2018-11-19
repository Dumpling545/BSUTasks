#include "practice5.h"
void lettersContains(ofstream fout, char * word1, char *word2, bool withRepeats){
    int length1 = strlen(word1);
    int length2 = strlen(word2);
    int  repeats[length1];
    for(int i = 0; i < length1; i++){
        repeats[i] = 0;
    }
    for(int i = 0; i < length1; i++){
        for(int j = i+1; j < length1; j++){
            if(word1[i] == word1[j]){
                repeats[j] = 1;
            }
        }
    }
    for(int i = 0; i < length1; i++){
        if(repeats[i] == 0){
            for(int j = 0; j < length2; j++){
                if(word1[i] == word2[j]){
                    fout << "yes ";
                    break;
                } else if(j == length1 -1){
                     fout << "no ";
                }
            }
        } else if(withRepeats){
            fout << "no ";
        }
    }
    fout <<endl;
}
char * getUniqueLetters(char * str){
    int length = strlen(str);
    char * res = new char[256];
    int  repeats[length];
    for(int i = 0; i < length; i++){
        if(isalpha(str[i])){
            repeats[i] = 0;
            str[i] = tolower(str[i]);
        } else {
            repeats[i] = 1;
        }
    }
    for(int i = 0; i < length; i++){
        for(int j = i+1; j < length; j++){
            if(str[i] == str[j]){
                repeats[i] = 1;
                repeats[j] = 1;
                break;
            }
        }
    }
    int c = 0;
    for(int i = 0; i < length; i++){
        if(repeats[i] == 0){
            res[c] = str[i];
            c++;
        }
    }
    res[c] = '\0';
    return res;
}
Word * getWordsCount(char * str, int &m){
    int length = strlen(str);
    const char * delims = " ,.-!?;()[]:";
    Word* words = new Word[length];
    int wordsLength = 0;
    for(int i = 0; i < length; i++){
        words[i].name = "";
        words[i].counter = 0;
    }
    char * wordName = strtok (str,delims);
    while (wordName != NULL){
        int i = 0;
        for(; i < wordsLength; i++){
            if(strcmp(wordName,words[i].name) == 0){
                words[i].counter++;
                break;
            }
        }
        if(i == wordsLength){
            Word w;
            w.name = wordName;
            w.counter = 1;
            words[wordsLength++] = w;
        }
        wordName = strtok (NULL, delims);
    }
    m = wordsLength;
    return words;
}
char * stringDivideSentences(char * &str, const char * delims){
    char * sentence = new char[1000];
    int length = strlen(str);
    int delimLength = strlen(delims);
    bool stop = false;
    int i = 0;
    for(; i < length; i++){
        for(int j = 0; j < delimLength; j++){
            if(str[i] == delims[j]){
                stop = true;
                break;
            }
        }
        if(stop){
            break;
        } else {
            sentence[i] = str[i];
        }
    }
    sentence[i] = NULL;
    if(i == 0){
        sentence = NULL;
    }
    if(i + 1 < strlen(str)){
        str = str + i + 1;
    } else {
        str = str + strlen(str);
    }
    return sentence;
}
char * findWordInAllSentences( char * str){
    const char * delims = ".!?";
    char * copystr = new char[1000];
    strcpy(copystr, str);
    char * sentence = stringDivideSentences(copystr,delims);
    int length1 = 0;
    int length2 = 0;
    int length3 = 0;
    Word * words1 = getWordsCount(sentence, length1);
    Word * words2= new Word[1000];
    Word * words3 = new Word[1000];
    sentence = stringDivideSentences (copystr, delims);
    char * result;
    if(sentence != NULL){
        while (sentence != NULL){
            words2 = getWordsCount(sentence, length2);
            for(int i = 0; i < length1; i++){
                for(int j = 0; j < length2; j++){

                    if(strcmp(words1[i].name,words2[j].name) == 0){
                        delete [] words3[length3].name;
                        words3[length3].name = new char[strlen(words1[i].name)];
                        strcpy(words3[length3].name, words1[i].name);
                        length3++;
                    }
                }
            }
            if(length3 == 0){
                break;
            }
            delete [] words1;
            delete [] words2;
            length1 = length3;
            length2 = 0;
            length3 = 0;
            words1 = new Word[length1];
            words2 = new Word[1000];
            for(int i = 0; i < length1; i++){
                words1[i].name = new char[1000];
            }
            for(int i = 0; i < length2; i++){
                words2[i].name = new char[1000];
            }
            for(int i = 0; i < length1; i++){
                strcpy(words1[i].name,words3[i].name);
            }
            delete [] words3;
            sentence = stringDivideSentences(copystr, delims);
        }
    } else {
        delete [] words3;
        words3 = words1;
        length3 = length1;
    }
    if(length3 == 0){
        result = NULL;
    } else {
        result = words3[0].name;
    }
    return result;
}