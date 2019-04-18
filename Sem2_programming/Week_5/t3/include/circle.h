#pragma once
#include <windows.h>
class Circle
{
    public:
        Circle();
        Circle(int x, int y, COLORREF color);
        void extend();
        void draw(HDC &hdc);
        bool isInternal(int x1, int y1);
    private:
        int delta = 5;
        int x;
        int y;
        int radius = 10;
        COLORREF color;
};
