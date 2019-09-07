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
Element * shuntingYard(char * str){
    int length = strlen(str);
    if(length == 1){
        return new Number(str[0] - '0', nullptr);
    }
    Element * current = nullptr;
    Stack<char> operationStack;
    bool numberStarted = false;
    for(int i = 0; i < length; i++){
        switch(str[i]){
            case '*':
            case '/':
                numberStarted = false;
                while(!operationStack.isEmpty() && (operationStack.first() == '*' || operationStack.first() == '/')){
                    current = operationFactory(operationStack.pop(), current);
                }
                operationStack.push(str[i]);
                break;
            case '+':
            case '-':
                numberStarted = false;
                while(!operationStack.isEmpty() && (operationStack.first() == '*' || operationStack.first() == '/'
                      || operationStack.first() == '+' || operationStack.first() == '-')){
                    current = operationFactory(operationStack.pop(), current);
                }
                operationStack.push(str[i]);
                break;
            case '(':
                numberStarted = false;
                operationStack.push('(');
                break;
            case ')':
                numberStarted = false;
                while(operationStack.first() != '('){
                    current = operationFactory(operationStack.pop(), current);
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
                if(!numberStarted){
                    current = new Number(str[i] - '0', current);
                    numberStarted = true;
                } else {
                    current->value = current->value * 10 + (str[i] - '0');
                }
                break;
            default:
                numberStarted = false;
                break;
        }
    }
    while(!operationStack.isEmpty()){
        current = operationFactory(operationStack.pop(), current);
    }
    return current;
}
double computeString(char * str){
    Element * rpnElement = shuntingYard(str);
    return rpnElement->compute();
}

Operation * operationFactory(char op, Element * previous){
    Operation * result;
    switch(op){
        case '*':
            result = new Multiply(previous);
            break;
        case '/':
            result = new Divide(previous);
            break;
        case '-':
            result = new Subtract(previous);
            break;
        case '+':
            result = new Add(previous);
            break;
    }
    return result;
}
