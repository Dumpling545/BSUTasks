#include "point.h"
Point::Point(const Point & p){
    this->x = p.x;
    this->y = p.y;
}
Point::Point(){
    x = 0;
    y = 0;
}
