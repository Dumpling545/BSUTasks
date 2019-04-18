#include "circle.h"
Circle::Circle(int x, int y,  COLORREF color)
{
    this->x = x;
    this->y = y;
    this->color = color;
}
Circle::Circle(){}
void Circle::extend(){
    radius+=delta;
}
bool Circle::isInternal(int x1, int y1){
    int x_sqr = (x1 - x)*(x1 - x);
    int y_sqr = (y1 - y)*(y1 - y);
    return x_sqr + y_sqr <= radius*radius;
}
void Circle::draw(HDC &hdc){
    HPEN pen = CreatePen(PS_SOLID, 3, color);
    SelectObject(hdc, pen);
    Ellipse(hdc, x-radius,y-radius, x+radius, y + radius);
    DeleteObject(pen);
}
