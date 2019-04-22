#pragma once
#include "movable.h"
#include "drawableitem.h"
class DynamicDrawableItem : public DrawableItem, public Movable
{
    public:
        DynamicDrawableItem();
        virtual void move(int dx, int dy) = 0;
        virtual bool isDynamic();
};
