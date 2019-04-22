#pragma once
#include "drawable.h"
class DrawableItem : public Drawable
{
    public:
        DrawableItem();
        COLORREF color;
        virtual RECT border() = 0;
        virtual void draw (HDC &hdc) = 0;
        virtual bool isDynamic();
};
