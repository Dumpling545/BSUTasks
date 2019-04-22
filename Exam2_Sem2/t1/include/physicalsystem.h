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
        double phi_start;
        double phi_collision;
        void init();
        void draw(HDC &hdc);
        void execute(int delta_t);
        void setColor(int x, int y);
        void setAcceleration(int a);
    protected:
        double g = 100;
        int phase = 1;
        double w;
        double offset_t_falsephysics = 0;
        double delta_angle = 0;
        double angle_speed_falsephysics = 0;
        int active = 0;
        std::vector<BallOnThread> balls;
};
