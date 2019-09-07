#pragma once
#include "rational.h"
class Operation
{
    public:
        Operation();
        Operation(Rational op1, Rational op2, char type);
        char type;
        Rational operand1;
        Rational operand2;
};
