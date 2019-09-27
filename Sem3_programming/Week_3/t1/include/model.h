#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "inputinfo.h"
#include "outputinfo.h"
#include "set.h"
#include "setiterator.h"
#include "visitor.h"
class Model
{
    public:
        Model();
        OutputInfo refresh(InputInfo inputInfo);
    private:
        std::string dbl_to_str(double d);
};
