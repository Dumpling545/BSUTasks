#pragma once
#include <cmath>
#include <iostream>
#include "triangle.h"
using namespace std;
class TriangleController final{
    public:
        static long double precision;
        static Triangle largestTriangle(Triangle * triangles, int length);
        static void moveTriangle(Triangle  &triangle, long double x, long double y);
        static bool contains(const Triangle container, const Triangle content);
        static void printTriangle(const Triangle tr, ostream& _fout);
        static long double computeArea(Triangle triangle);
    private:
        TriangleController();
        //static double computeSquaredArea(Triangle triangle);

};
