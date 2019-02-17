#pragma once
template<class T>
class SLL_element
{
    public:
        T value;
        SLL_element(T value, SLL_element* next = nullptr){
            this->value = value;
            this->next = next;
        }
        SLL_element(const SLL_element& source){
            value = source.value;
            next = source.next;
        }
        SLL_element * next;
};
