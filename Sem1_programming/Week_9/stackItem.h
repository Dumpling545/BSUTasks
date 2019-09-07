#pragma once
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
