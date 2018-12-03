#pragma once
#include <string>
#include <cstdlib>
#include "operationValidator.h"
#include <cctype>
#include "invalidOperationException.h"
#include "mathException.h"
#include "operation.h"
#include "rational.h"
class OperationParser{
    public:
        OperationParser();
        Operation parseString(string unparsed);
        string deparseRational(Rational rational);
    private:
        OperationValidator * validator;
        Rational parseOperand(string unparsedOperand);
};
