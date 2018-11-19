#pragma once
#include "add.h"
double Add::compute(){
    double p2 = previous->compute();
    previous = previous->previous;
    previous->next = this;
    double p1 = previous->compute();
    if(next != nullptr){
        next->previous = previous;
        next->previous->next = next;
    }
    return p2 + p1;
}
Add::Add(Element * previous) : Operation(previous){}
