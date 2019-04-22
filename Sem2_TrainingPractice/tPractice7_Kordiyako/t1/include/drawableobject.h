#pragma once
#include <windows.h>
#include "drawableitem.h"
#include "map"
#include "drawable.h"
class DrawableObject : public Drawable
{
    public:
        DrawableObject();
        RECT border();
        void draw (HDC &hdc);
        ~DrawableObject();
    protected:
        std::map<int, DrawableItem*> items;
};
