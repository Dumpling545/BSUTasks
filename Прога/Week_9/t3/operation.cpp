#pragma once
#include "operation.h"
/**double Operation::compute(){
    parseToNumber(computeValue());
    return 0;
}
void Operation::parseToNumber(double n){
    Number num(n);
    num.previous = nullptr;
    num.next = next;
    next.previous = num;
}*/
Operation::Operation(Element * previous){
    this->previous = previous;
    if(previous != nullptr){
        previous->next = this;
    }
    this->next = nullptr;
}
double Operation::compute(){
    return 0;
}
Operation::Operation(){
    this->previous = nullptr;
    this->next = nullptr;
}
