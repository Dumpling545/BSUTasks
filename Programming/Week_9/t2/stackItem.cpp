#include "stackItem.h"
template <class T>
StackItem<T>::StackItem(T* value, StackItem* previous){
    this->previous = previous;
    this->value = value;
}

