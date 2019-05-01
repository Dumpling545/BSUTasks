#pragma once
#include "fishermaninfo.h"
#include "fisherman.h"
#include <windows.h>
#include <vector>
#include <numeric>
#include <iomanip>
#include <sstream>
#include <iomanip>
#include <tchar.h>
#include <algorithm>
extern const int SIGNATURE_PRECISION;
extern int red_coef;
extern int green_coef;
extern int blue_coef;
extern int text_size;
class Diagram
{
    public:
        Diagram();
        void addData(Fisherman fisherman);
        virtual void draw(HDC &hdc, RECT drawingArea) = 0;
    protected:
        int margin = 1;
        SIZE getMaxLastNameSize(HDC &hdc);
        double getMaxWeight();
        double getWeightSum();
        std::vector<FishermanInfo> info;
};
