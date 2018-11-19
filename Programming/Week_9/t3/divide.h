#pragma once
#include "operation.h"
class Divide : public Operation{
    public:
        Divide(Element * previous);
        double compute();
};
