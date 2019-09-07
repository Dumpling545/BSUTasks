#pragma once
#include "operation.h"
class Subtract : public Operation{
    public:
        Subtract(Element * previous);
        double compute();
};
