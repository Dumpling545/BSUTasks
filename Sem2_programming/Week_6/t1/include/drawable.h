#pragma once
#include <windows.h>
class Drawable
{
    public:
        Drawable();
        int x;
        int y;
        virtual RECT border() = 0;
        virtual void draw (HDC &hdc) = 0;
};
