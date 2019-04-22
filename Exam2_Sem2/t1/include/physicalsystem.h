#pragma once
#include <windows.h>
#undef __STRICT_ANSI__
#include "ballonthread.h"
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#define _USE_MATH_DEFINES
class PhysicalSystem
{
    public:
        PhysicalSystem();
        PhysicalSystem(int thread_x, int thread_y,
                       int length, int radius, double startAngle,  int n);
        int thread_x;
        int thread_y;
        int length;
        int radius;
        int n;
        double startAngle;
        void init();
        void draw(HDC &hdc);
        void execute(int delta_t);
        void setColor(int x, int y);
    private:
        int phase = 1;
        double g =0.007;
        double speed_current = 0;
        int active = 0;
        double speed_coefficient = 1;
        bool ballsTouched(int i, int j);
        std::vector<BallOnThread> balls;
};
