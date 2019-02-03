#include "practice9.h"
int triangleType(int a, int b, int c){
/*Method returns -1, if triangle with such edges can't exist; 0, if all edges are different;
 1, if two edges are equivalent; 2, if all edges are equivalent*/
    long long d_a = a;
    long long d_b = b;
    long long d_c = c;
    if(d_a + d_b <= d_c || d_a + d_c <= d_b || d_b + d_c <= d_a){
        return -1;
    } else if(a == b || a == c || b == c){
        if(a == b && a == c){
            return 2;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}
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
            } else if(str[i] == closeBrackets[j] && (brackets.isEmpty() || brackets.pop() != openBrackets[j])){
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
char * minMaxShuntingYard(char * str){
    int length = strlen(str);
    if(length == 1){
        return str;
    }
    Stack<char> operationStack;
    char * result = new char[length];
    int c = 0;
    for(int i = 0; i < length; i++){
        switch(str[i]){
            case 'm':
                if(str[i+1] == 'a'){
                    operationStack.push('M');
                } else {
                    operationStack.push('m');
                }
                i+=2;
                break;
            case '(':
                operationStack.push('(');
                break;
            case ')':
                while(operationStack.first() != '('){
                    result[c] = operationStack.pop();
                    c++;
                }
                operationStack.pop();
                result[c] = operationStack.pop();
                c++;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                result[c] = str[i];
                c++;
                break;

        }
    }
    while(!operationStack.isEmpty()){
        result[c] = operationStack.pop();
        c++;
    }
    for(; c < length; c++){
        result[c] = NULL;
    }
    return result;
}
int computeMinMaxString(char * str){
    char * rpnString = minMaxShuntingYard(str);
    int length = strlen(rpnString);
    Stack<char> minMaxStack;
    char op1;
    char op2;
    for(int i = 0; i < length; i++){
        switch(rpnString[i]){
            case 'm':
                op1 = minMaxStack.pop();
                op2 = minMaxStack.pop();
                minMaxStack.push(std::min(op1, op2));
                break;
            case 'M':
                op1 = minMaxStack.pop();
                op2 = minMaxStack.pop();
                minMaxStack.push(std::max(op1, op2));
                break;
            default:
                minMaxStack.push(rpnString[i]);
                break;
        }
    }
    return minMaxStack.pop() - '0';
}
