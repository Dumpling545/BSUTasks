#include "operationController.h"
void OperationController::runOperations(){

}
string OperationController::getResult(){
    int length = result.size();
    string s;
   /* for(int i = 0; i < length;i++){
        s +=
    }*/
    return "";
}
void OperationController::createOperations(vector<string> unparsed){
    operations.clear();
    int length = unparsed.size();
    for(int i = 0; i < length; i++){
        Operation op;
        try{
            op = parser->parseString(unparsed[i]);
        } catch(InvalidOperationException &e){
            //logger
            continue;
        }
        operations.push_back(op);
    }
}
Rational OperationController::run(Operation op){
    Rational r;
    switch(op.type){
        case '+':
            r = op.operand1 + op.operand2;
            break;
        case '-':
            r = op.operand1 - op.operand2;
            break;
        case '*':
            r = op.operand1 * op.operand2;
            break;
        case '/':
            r = op.operand1 / op.operand2;
            break;
    }
    return r;
}
void OperationController::runOperations(){
    result.clear();
    int length = operations.size();
    for(int i = 0; i < length; i++){
        result.push_back(run(operations[i]));
    }
}
OperationController::OperationController(){
    parser = new OperationParser();
}
