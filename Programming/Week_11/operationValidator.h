#pragma once
#include <string>
using namespace std;
class OperationValidator{
    public:
        OperationValidator();
        bool validateRational(int numerator, int denominator);
        bool validateOperationType(string type);
};

