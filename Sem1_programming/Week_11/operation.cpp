#include "operation.h"
Operation::Operation(){}
Operation::Operation(Rational op1, Rational op2, char type){
    operand1 = op1;
    operand2 = op2;
    this->type = type;
}
