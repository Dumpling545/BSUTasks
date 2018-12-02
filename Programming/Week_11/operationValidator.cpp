#include "operationValidator.h"
OperationValidator::OperationValidator(){}
bool OperationValidator::validateRational(int numerator, int denominator){
    return (denominator != 0);
}
bool OperationValidator::validateOperationType(string type){
    if(type.empty() || type.size() != 1){
        return false;
    } else {
        switch(type[0]){
            case '+':
            case '*':
            case '/':
            case '-':
                return true;
                break;
            default:
                return false;
        }
    }
}
