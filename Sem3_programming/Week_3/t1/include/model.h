#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
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
        void addElement(Element * element);
    private:
        std::vector<Element*> elements;
        std::string dbl_to_str(double d);
};
