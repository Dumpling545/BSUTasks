#pragma once
#include <iostream>
#include "complexNumber.h"
#include "stackItem.h"
template <class T>
class Queue
{
    public:
        Queue(){}
        bool isEmpty(){
            return firstItem == nullptr;
        }
        T first(){
            return firstItem->value;
        }
        T pop(){
            T tempVal = firstItem->value;
            StackQueueItem<T> * newFirst = firstItem->previous;
            delete  firstItem;
            firstItem = newFirst;
            return tempVal;
        }
        void push(T item){
            if(firstItem != nullptr){
                StackQueueItem<T> *lastItem = firstItem;
                while(lastItem->previous!= nullptr){
                    lastItem = lastItem->previous;
                }
                lastItem->previous = new StackQueueItem<T>(item, nullptr);
            } else {
                firstItem = new StackQueueItem<T>(item, nullptr);
            }

        }
    private:
        StackQueueItem<T> *firstItem = nullptr;
        //StackQueueItem<T> *lastItem = nullptr;
};
