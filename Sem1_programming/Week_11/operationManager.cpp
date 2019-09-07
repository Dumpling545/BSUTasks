#include "operationManager.h"
string OperationManager::getResult(){
    int length = result.size();
    string s;
    for(int i = 0; i < length;i++){
        s += (parser->deparseRational(result[i]) + "\n");
    }
    return s;
}
void OperationManager::createOperations(vector<string> unparsed){
    operations.clear();
    int length = unparsed.size();
    for(int i = 0; i < length; i++){
        Operation op;
        try{
            op = parser->parseString(unparsed[i]);
            operations.push_back(op);
        } catch(InvalidOperationException &e){
            Logger::warning(e.what());
        }catch(MathException &e){
            Logger::warning(e.what());
        }
    }
    Logger::info("Operations are created");
}
Rational OperationManager::run(Operation op){
    Rational r;
    r = op.operand1;
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
void OperationManager::runOperations(){
    result.clear();
    int length = operations.size();
    for(int i = 0; i < length; i++){
        result.push_back(run(operations[i]));
    }
    Logger::info("Operations are runned");
}
OperationManager::OperationManager(){
    parser = new OperationParser();
}
