#pragma once
#include "dynamicdrawableitem.h"
#include <windows.h>
class BallOnThread : public DynamicDrawableItem
{
    public:
        BallOnThread();
        BallOnThread(int x, int y, int thread_x, int thread_y,
                     int radius, COLORREF color);
        void move(int dx, int dy);
        void draw(HDC& hdc);
        RECT border();
        int thread_x;
        int thread_y;
        int radius;
    protected:
};
