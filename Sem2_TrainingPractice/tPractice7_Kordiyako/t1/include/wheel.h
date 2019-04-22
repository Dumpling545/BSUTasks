#pragma once
#define _USE_MATH_DEFINES
#undef __STRICT_ANSI__
#include "dynamicdrawableitem.h"
#include <windows.h>
#include <cmath>
class Wheel : public DynamicDrawableItem
{
    public:
        int amountOfSpokes = 10;
        Wheel();
        Wheel(int x, int y, int r, COLORREF color);
        int radius;
        double angle = 0;
        RECT border();
        void draw (HDC &hdc);
        void move(int dx, int dy);
};
