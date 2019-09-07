#pragma once
#include "subtract.h"
double Subtract::compute(){
    double p2 = previous->compute();
    previous = previous->previous;
    previous->next = this;
    double p1 = previous->compute();
    if(next != nullptr){
        next->previous = previous;
        next->previous->next = next;
    }
    return p1 - p2;
}
Subtract::Subtract(Element * previous): Operation(previous){}
