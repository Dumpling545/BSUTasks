#pragma once
#include "coloureddetail.h"
class Wheel : public ColouredDetail
{
    public:
        int getColor();
        Wheel();
        Wheel(int color);
};
