#include "week9.h"
bool isCorrectBrackets(char* str){
    Stack<char> brackets;
    int length = strlen(str);
    char  openBrackets[] = {'(', '[', '{'};
    char  closeBrackets[] = {')', ']', '}'};
    bool isCorrect = true;
    for(int i = 0; i < length && isCorrect; i++){
        for(int j = 0; j < 3; j++){
            if(str[i] == openBrackets[j]){
                brackets.push(str[i]);
                break;
            } else if(str[i] == closeBrackets[j] && brackets.pop() != openBrackets[j]){
                isCorrect = false;
                break;
            }
        }
    }
	if(!brackets.isEmpty()){
		isCorrect = false;
	}
    return isCorrect;
}
bool isCorrectInputFile(ifstream &_fin){
    if(_fin &&  _fin.peek() != ifstream::traits_type::eof()){
        return true;
    } else {
        cout << "Input file doesn't exist or empty" << endl;
        return false;
    }
}