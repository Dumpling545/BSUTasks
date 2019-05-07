#pragma once
#include <vector>
#include "reversable.h"
#include "dynamicdrawableitem.h"
class PolygonalItem : public DynamicDrawableItem, public Reversable
{
    public:
        PolygonalItem();
        PolygonalItem(int x, int y, std::vector<POINT> points, COLORREF color);
        RECT border();
        void draw (HDC &hdc);
        void move(int dx, int dy);
        void onReverse();
        std::vector<POINT> points;
};
