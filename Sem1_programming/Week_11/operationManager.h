#pragma once
#include <string>
#include <vector>
#include "logger.h"
#include "operation.h"
#include "operationParser.h"
#include "invalidOperationException.h"
#include "rational.h"
using namespace std;
class OperationManager{
    public:
        OperationManager();
        void createOperations(vector<string> unparsed);
        void runOperations();
        string getResult();
    private:
        vector<Rational> result;
        vector<Operation> operations;
        OperationParser * parser;
        Rational run(Operation operation);

};
