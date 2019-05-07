#pragma once
#include "movable.h"
#include "drawable.h"
#include "wheel.h"
#include "rectangleitem.h"
#include "reversable.h"
#include "polygonalitem.h"
#include "dynamicdrawableobject.h"
#include <iostream>
class Car : public DynamicDrawableObject, public Reversable{
    public:
        Car(int x, int y, int carHeight, COLORREF bodyColor, COLORREF topColor,
            COLORREF windowColor, COLORREF lightColor, COLORREF wheelColor);
        enum ItemFlag{
            CarBody,
            CarTop,
            Window_1,
            Window_2,
            Light_1,
            Light_2,
            Wheel_1,
            Wheel_2
        };
        COLORREF getItemColor(ItemFlag flag);
        void setItemColor(ItemFlag flag, COLORREF newColor);
        void onReverse();
    private:
        void initItems(COLORREF bodyColor, COLORREF topColor,
                COLORREF windowColor, COLORREF lightColor, COLORREF wheelColor);
        int blockSize = 10;
};
