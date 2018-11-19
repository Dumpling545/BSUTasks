#include "number.h"
double Number::compute(){
    return value;
}
Number::Number(double n, Element * previous){
    value = n;
    this->previous = previous;
    if(previous != nullptr){
        previous->next = this;
    }
    this->next = nullptr;
}
