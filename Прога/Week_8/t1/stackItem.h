#pragma once
#include "complexNumber.h"
template <class T>
class StackQueueItem
{
    public:
        StackQueueItem(T value, StackQueueItem<T>* previous){
            this->previous = previous;
            this->value = value;
        }
        T value;
        StackQueueItem* previous;
};
