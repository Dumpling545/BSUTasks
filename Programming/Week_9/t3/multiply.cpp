#pragma once
#include "multiply.h"
double Multiply::compute(){
    double p2 = previous->compute();
    previous = previous->previous;
    previous->next = this;
    double p1 = previous->compute();
    if(next != nullptr){
        next->previous = previous;
        next->previous->next = next;
    }
    return p1 * p2;
}
Multiply::Multiply(Element * previous): Operation(previous){}
