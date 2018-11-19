#pragma once
#include "element.h"
class Operation : public Element
{
    public:
        Operation(Element * previous);
        Operation();
        virtual double compute();
};
