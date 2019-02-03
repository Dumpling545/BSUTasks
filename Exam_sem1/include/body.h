#pragma once
#include "coloureddetail.h"
class Body : public ColouredDetail
{
    public:
        int getColor();
        Body();
        Body(int color);
};
