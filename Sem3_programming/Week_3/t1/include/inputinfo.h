#pragma once
#include "visitor.h"
class InputInfo
{
    public:
        Element* elems[2] = {nullptr, nullptr};
        InputInfo() {}
        ~InputInfo() {delete [] elems;}
};
