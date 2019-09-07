#pragma once
#include "element.h"
class Number : public Element
{
    public:
        Number(double n, Element * previous);
        double compute();
};
