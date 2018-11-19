#include <iostream>
#include <fstream>
using namespace std;
/** Из текста удалить все слова заданной длины, начинающиеся на согласную.
    Выполнил: Ян Кордияко

    Input                                                                                   Output
    ------------------------------------------------------------------------------------------------------------------------------
    qwertysfeef kghf addf, jityfo Jnas mivc eory Yofc. Ksqa a c tddd dddd! ccc              qwertysfeef  addf, jityfo   eory Yofc.  a c  ! ccc
    4

    aaa bbb ccc ddd eee fff ggg hhh iii jjj kkk lll mmm nnn ooo ppp qqq                     aaa    eee    iii      ooo
    3
*/
ofstream fout("output.txt");
ifstream fin("input.txt");
int strLength(char * str){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}
bool isLetter(char c){
    return (c >='A' && c <= 'Z') || (c >='a' && c <= 'z');
}
char upperCase(char c){
    char r = 0;
    if(c >='A' && c <= 'Z'){
        r = c;
    } else if(c >='a' && c <= 'z'){
        r = c - 32;
    }
    return r;
}
void removeStartWith(char* str, char c, int n){
    int length = strLength(str);
    bool isSufficientWord = false;
    for(int i = 0; i < length - n + 1; i++){
        if(str[i] == c){
            isSufficientWord = true;
            for(int j = 0; j < n; j++){
                if(!isLetter(str[i + j])){
                    isSufficientWord = false;
                    break;
                }
            }
            if(i + n < length && isLetter(str[i + n])){
                isSufficientWord = false;
            }
            if(i > 0 && isLetter(str[i - 1])){
                isSufficientWord = false;
            } else if(isSufficientWord){
                for(int j = i; j < length - n; j++){
                    str[j] = str[j + n];
                }
                for(int k = length - n; k < length; k++){
                    str[k] = '\0';
                }
                length-=n;
            }
        }
    }
}
void removeStartWithConsonants(char* str, int n){
    char* consonants = "bcdfghjklmnpqrstvwxz";
    int length = strLength(consonants);
    for(int i = 0; i < length; i++){
        removeStartWith(str, consonants[i], n);
        removeStartWith(str, upperCase(consonants[i]), n);
    }
}
int main()
{
    int m = 1000;
    int n;
    char * str = new char[m];
    fin.getline(str, m);
    fin >> n;
    removeStartWithConsonants(str, n);
    for(int i = 0; i < strLength(str); i++){
        fout << str[i];
    }
    system("pause");
    return 0;
}
