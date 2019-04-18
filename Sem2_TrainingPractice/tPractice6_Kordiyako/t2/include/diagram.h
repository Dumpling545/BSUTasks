#pragma once
#include "fishermaninfo.h"
#include "fisherman.h"
#include <windows.h>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
class Diagram
{
    public:
        Diagram();
        void addData(Fisherman fisherman);
        virtual void draw(HDC &hdc, RECT drawingArea) = 0;
    protected:
        std::vector<FishermanInfo> info;
};
