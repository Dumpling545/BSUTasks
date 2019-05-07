#include "reversable.h"

Reversable::Reversable()
{
    //ctor
}
void Reversable::reverse(){
    direction = ((direction == Direction::FORWARD) ?
                                Direction::BACKWARD : Direction::FORWARD);
    onReverse();
}
