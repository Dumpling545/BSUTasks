#pragma once
#include "point.h"
class Triangle{
    public:
        Point points[3];
        Triangle(Point * points);
        Triangle(const Triangle &t);
        Triangle();
};
