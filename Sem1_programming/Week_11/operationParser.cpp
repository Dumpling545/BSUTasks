#include "operationParser.h"
OperationParser::OperationParser(){
    validator = new OperationValidator();
}
Operation OperationParser::parseString(string unparsed){
    size_t space1 = unparsed.find(" ");
    size_t space2 = unparsed.rfind(" ");
    Rational r1, r2;
    char op_res_type;
    Operation res;
    string op1, op2, type;
    if(space1 == string::npos){
        op1 = unparsed.substr(0, space1);
    } else if(space2 != space1){
        op1 = unparsed.substr(0, space1);
        type = unparsed.substr(space1 + 1, space2 - space1 - 1);
        op2 = unparsed.substr(space2 + 1, unparsed.size() - space2 - 1);
    } else {
        throw InvalidOperationException("'" + unparsed + "'");
    }
    try{
        r1 = parseOperand(op1);
        res.operand1 = r1;
        if(!op2.empty()){
            r2 = parseOperand(op2);
            if(validator->validateOperationType(type)){
            op_res_type = type[0];
                if(op_res_type == '/' && r2.getNumerator() == 0){
                    throw MathException();
                }
            } else {
                throw InvalidOperationException("invalid operator");
            }
            res = Operation(r1, r2, op_res_type);
        } else {
            res.operand1 = r1;
            res.type  = 0;
        }
    } catch(InvalidOperationException &e){
        e.operation += (" in '" + unparsed +"'");
        throw e;
    } catch(MathException &e){
        InvalidOperationException ioe(string(e.what()) + " in '" + unparsed + "'");
        throw ioe;
    }
    return res;
}
Rational OperationParser::parseOperand(string unparsedOperand){
    int sign = 1;
    int numerator = 0;
    int denominator = 0;
    int *variable = &numerator;
    int length = unparsedOperand.size();
    if (length == 0){
        throw InvalidOperationException("null operand");
    }
    bool findSlash = false;
    int i = 0;
    if(unparsedOperand[0] == '-'){
        sign = -1;
        i++;
    }
    for(; i < length; i++){
        char temp = unparsedOperand[i];
        if(isdigit(temp)){
            (*variable)*=10;
            (*variable)+=(temp-'0');
        } else if(!findSlash && temp =='/'){
            findSlash = true;
            variable = &denominator;
        } else {
            throw InvalidOperationException("'" + unparsedOperand + "'");
        }
    }
    numerator *= sign;
    if(!findSlash){
        denominator = 1;
    }
    if(validator->validateRational(numerator, denominator)){
        return Rational(numerator, denominator);
    } else {
        throw MathException();
    }
}
string OperationParser::deparseRational(Rational rational){
    string res = to_string(rational.getNumerator());
    if(rational.getDenominator() != 1){
        res += ("/" +  to_string(rational.getDenominator()));
    }
    return res;
}
