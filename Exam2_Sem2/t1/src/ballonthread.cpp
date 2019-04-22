#include "../include/ballonthread.h"

BallOnThread::BallOnThread()
{
    //ctor
}
BallOnThread::BallOnThread(int x, int y, int thread_x, int thread_y,
                     int radius, COLORREF color){
    this->x = x;
    this->y = y;
    this->thread_x = thread_x;
    this->thread_y = thread_y;
    this->radius = radius;
    this->color = color;
}
void BallOnThread::move(int dx, int dy){
    x+=dx;
    y+=dy;
}
void BallOnThread::draw(HDC& hdc){
    MoveToEx(hdc, thread_x, thread_y, NULL);
    LineTo(hdc, x, y);
    HBRUSH brush = CreateSolidBrush(color);
    SelectObject(hdc, brush);
    Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
    DeleteObject(brush);
}
RECT BallOnThread::border(){
    RECT result;
    result.left = x - radius;
    result.right = x + radius;
    result.top = y - radius;
    result.bottom = y + radius;
}
