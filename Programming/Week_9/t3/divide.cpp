#pragma once
#include "divide.h"
double Divide::compute(){
    double p2 = previous->compute();
    previous = previous->previous;
    previous->next = this;
    double p1 = previous->compute();
    if(next != nullptr){
        next->previous = previous;
        next->previous->next = next;
    }
    return p1 / p2;
}
Divide::Divide(Element * previous) : Operation(previous){}
