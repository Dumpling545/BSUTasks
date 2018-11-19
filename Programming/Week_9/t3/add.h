#pragma once
#include "operation.h"
class Add : public Operation{
    public:
        Add(Element * previous);
        double compute();
};
