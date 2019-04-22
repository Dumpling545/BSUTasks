#include "rectangleitem.h"
RectangleItem::RectangleItem()
{
    //ctor
}
RectangleItem::RectangleItem(int x, int y,
                             int width, int height,
                             COLORREF color){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
}
RECT RectangleItem::border(){
    RECT rect;
    SetRect(&rect, x - width/2, y - height/2, x + width/2, y + height/2);
    return rect;
}
void RectangleItem::draw(HDC &hdc){
    RECT rect = border();
    FillRect(hdc, &rect, CreateSolidBrush(color));
}

void RectangleItem::move(int dx, int dy){
    x+=dx;
    y+=dy;
}
