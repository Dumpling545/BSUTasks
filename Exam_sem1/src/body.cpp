#include "body.h"

Body::Body()
{
    //ctor
}
Body::Body(int color)
{
    this->color = color;
}
int Body::getColor(){
    return this->color;
}
