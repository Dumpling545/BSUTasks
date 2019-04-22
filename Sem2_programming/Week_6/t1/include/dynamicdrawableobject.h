#pragma once
#include "drawableobject.h"
#include "movable.h"
#include "dynamicdrawableitem.h"
class DynamicDrawableObject : public DrawableObject, public Movable
{
    public:
        DynamicDrawableObject();
        //~DynamicDrawableObject();
        void move(int dx, int dy);
};
