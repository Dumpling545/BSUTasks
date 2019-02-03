#include "wheel.h"

Wheel::Wheel()
{
    //ctor
}
Wheel::Wheel(int color)
{
    this->color = color;
}
int Wheel::getColor(){
    return this->color;
}
