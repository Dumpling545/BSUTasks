#pragma once
#include "fishermaninfo.h"
#include "fisherman.h"
#include <windows.h>
#include <vector>
#include <numeric>
#include <iomanip>
#include <sstream>
#include <iomanip>
#include <algorithm>
extern const int SIGNATURE_PRECISION;
class Diagram
{
    public:
        Diagram();
        void addData(Fisherman fisherman);
        virtual void draw(HDC &hdc, RECT drawingArea) = 0;
    protected:
        int margin = 1;
        int getMaxLastNameLengthIndex();
        double getMaxWeight();
        double getWeightSum();
        std::vector<FishermanInfo> info;
};
