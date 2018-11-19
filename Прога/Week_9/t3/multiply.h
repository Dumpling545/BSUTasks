#pragma once
#include "operation.h"
class Multiply : public Operation{
    public:
        Multiply(Element * previous);
        double compute();
};
