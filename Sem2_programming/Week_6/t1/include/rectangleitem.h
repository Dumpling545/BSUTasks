#pragma once
#include "dynamicdrawableitem.h"
class RectangleItem : public DynamicDrawableItem
{
    public:
        RectangleItem();
        RectangleItem(int x, int y, int width, int height, COLORREF color);
        RECT border();
        int width;
        int height;
        void draw (HDC &hdc);
        void move(int dx, int dy);
};
