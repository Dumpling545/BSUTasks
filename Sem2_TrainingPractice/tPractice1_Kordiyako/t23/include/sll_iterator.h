#pragma once
#include "sll_element.h"
#include <iostream>
template<class T>
class SLL_iterator
{
    public:
        SLL_iterator(SLL_element<T> * current){
            this->current = current;
        }
        SLL_iterator operator ++(int){
            current = current->next;
            return (*this);
        }
        T get(){
            return current->value;
        }
        const bool operator == (const SLL_iterator &it2)
        {
            return current == it2.current;
        }
        const bool operator != (const SLL_iterator &it2)
        {
            return !((*this) == it2);
        }
    private:
        SLL_element<T> * current;
};
