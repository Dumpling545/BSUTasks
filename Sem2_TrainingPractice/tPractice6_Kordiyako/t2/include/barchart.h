#pragma once
#include "diagram.h"
class BarChart : public Diagram
{
    public:
        BarChart();
        void draw(HDC &hdc, RECT drawingArea);
};
