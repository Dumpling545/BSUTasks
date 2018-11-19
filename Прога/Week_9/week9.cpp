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
bool isCorrectInputFile(ifstream &_fin){
    if(_fin &&  _fin.peek() != ifstream::traits_type::eof()){
        return true;
    } else {
        cout << "Input file doesn't exist or empty" << endl;
        return false;
    }
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
    int op1;
    int op2;
    for(int i = 0; i < length; i++){
        switch(rpnString[i]){
            case 'm':
                op1 = minMaxStack.pop();
                op2 = minMaxStack.pop();
                minMaxStack.push(min(op1, op2));
                break;
            case 'M':
                op1 = minMaxStack.pop();
                op2 = minMaxStack.pop();
                minMaxStack.push(max(op1, op2));
                break;
            default:
                minMaxStack.push(rpnString[i]);
                break;
        }
    }
    return minMaxStack.pop() - '0';
}
char * shuntingYard(char * str){
    int length = strlen(str);
    if(length == 1){
        return str;
    }
    Stack<char> operationStack;
    char * result = new char[2*length];
    int c = 0;
    for(int i = 0; i < length; i++){
        switch(str[i]){
            case '*':
            case '/':
                while(!operationStack.isEmpty() && (operationStack.first() == '*' || operationStack.first() == '/')){
                    result[c++] = ' ';
                    result[c] = operationStack.pop();
                    c++;
                }
                result[c] = ' ';
                c++;
                operationStack.push(str[i]);
                break;
            case '+':
            case '-':
                while(!operationStack.isEmpty() && (operationStack.first() == '*' || operationStack.first() == '/'
                      || operationStack.first() == '+' || operationStack.first() == '-')){
                    result[c++] = ' ';
                    result[c] = operationStack.pop();
                    c++;
                }
                result[c] = ' ';
                c++;
                operationStack.push(str[i]);
                break;
            case '(':
                operationStack.push('(');
                break;
            case ')':
                while(operationStack.first() != '('){
                    result[c++] = ' ';
                    result[c] = operationStack.pop();
                    c++;
                }
                result[c++] = ' ';
                operationStack.pop();
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
        result[c++] = ' ';
        result[c] = operationStack.pop();
        c++;
    }
    for(; c < 2*length; c++){
        result[c] = NULL;
    }
    return result;
}
double computeString(char * str){
    char * rpnString = shuntingYard(str);
    int length = strlen(rpnString);
    Stack<double> simpleOperationStack;
    double op1;
    double op2;
    double op3;
    char * w = strtok (rpnString," ");
    char copyW[100];
    char op_res[100];
    while (w != NULL){
        strcpy(copyW, w);
        if(copyW[0] >= '0' && copyW[0] <= '9'){
            simpleOperationStack.push(atof(copyW));
        }else{
            op1 = simpleOperationStack.pop();
            op2 = simpleOperationStack.pop();
            op3 = 0;
            switch(copyW[0]){
                case '*':
                    op3 = op2 * op1;
                    break;
                case '/':
                    op3 = op2 / op1;
                    break;
                case '+':
                    op3 = op2 + op1;
                    break;
                case '-':
                    op3 = op2 - op1;
                    break;
            }
            simpleOperationStack.push(op3);
        }
        w = strtok (NULL, " ");
    }
    return simpleOperationStack.pop();
}
