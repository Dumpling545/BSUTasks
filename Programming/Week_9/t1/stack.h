#pragma once
#include "stackItem.h"
template <class T>
class Stack
{
    public:
        Stack(){}
        bool isEmpty(){
            return firstItem == nullptr;
        }
        T first(){
            return (firstItem->value);
        }
        T pop(){
            T tmp = firstItem->value;
            firstItem = firstItem->previous;
            return tmp;
        }
        void push(T item){
            firstItem = new StackQueueItem<T>(item, firstItem);
        }
    private:
        StackQueueItem<T> *firstItem = nullptr;
};
