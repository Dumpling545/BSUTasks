
#include "coloureddetail.h"

ColouredDetail::ColouredDetail()
{
}
bool ColouredDetail::operator==(ColouredDetail detail){
    return this->color == detail.color;
}
bool ColouredDetail::operator>=(ColouredDetail detail){
    return this->color >= detail.color;
}
int ColouredDetail::getColor(){
    return color;
}
