#include "wheel.h"

Wheel::Wheel()
{
    //ctor
}
Wheel::Wheel(int x, int y, int radius, COLORREF color){
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->color = color;
}
RECT Wheel::border(){
    RECT rect;
    SetRect(&rect, x - radius, y - radius, x + radius, y + radius);
    return rect;
}
void Wheel::draw(HDC &hdc){
    HBRUSH brush = CreateSolidBrush(color);
    SelectObject(hdc, brush);
    Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
    DeleteObject(brush);
    double spokeAngle = (2*M_PI) / (1.0 * amountOfSpokes);
    for(int i = 0; i < amountOfSpokes; i++){
        MoveToEx(hdc, x, y, NULL);
        LineTo(hdc, x + radius*cos(angle), y + radius*sin(angle));
        angle += spokeAngle;
    }
}
void Wheel::move(int dx, int dy){
    x += dx;
    y += dy;
    angle += dx / (1.0*radius);
}
