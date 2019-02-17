#pragma once
#include "sll_element.h"
#include "sll_iterator.h"

template<class T>
class SLL_vector
{
    public:
        SLL_vector(){
            first = nullptr;
        }
        SLL_vector(const SLL_vector<T> & source){
            int source_size = source.size();
            if(source_size != 0){
                first = new SLL_element<T>(source.first->value);
                SLL_element<T> * temp = first;
                SLL_element<T> * source_temp = source.first;
                for(int i = 1; i < source_size; i++){
                    temp->next = new SLL_element<T>(source_temp->next->value);
                    temp = temp->next;
                    source_temp = source_temp->next;
                }
            }
        }
        T & operator[](const int index) const{
            if(index < 0){
                throw "Out of range";
            } else {
                SLL_element<T> * temp = first;
                for(int i = 0; i < index; i++){
                    if(temp == nullptr){
                        throw "Out of range";
                    } else {
                        temp = temp->next;
                    }
                }
                return temp->value;
            }
        }
        int size() const{
            SLL_element<T> * temp = first;
            int s = 0;
            while(temp != nullptr){
                s++;
                temp = temp->next;
            }
            return s;
        }
        void push_back(const T& element){
            SLL_element<T> * elem = new SLL_element<T>(element);
            if(size() == 0){
                first = elem;
            } else {
                SLL_element<T> * temp = first;
                while(temp->next != nullptr){
                    temp = temp->next;
                }
                temp->next = elem;
            }
        }
        void push_front(const T& element){
            SLL_element<T> * elem = new SLL_element<T>(element, first);
            first = elem;
        }
        void insert(int pos, const T& element){
            if(pos == 0) push_front(element);
            else if(pos > 0){
                SLL_element<T> * temp = first;
                for(int i = 0; i < pos - 1; i++){
                    if(temp == nullptr){
                        throw "Out of range";
                    } else {
                        temp = temp->next;
                    }
                }
                temp->next = new SLL_element<T>(element, temp->next);
            } else {
                throw "Out of range";
            }
        }
        void erase(int pos){
            if(pos == 0) pop_front();
            else if(pos > 0){
                SLL_element<T> * temp = first;
                for(int i = 0; i < pos - 1; i++){
                    if(temp == nullptr){
                        throw "Out of range";
                    } else {
                        temp = temp->next;
                    }
                }
                SLL_element<T> * temp2 = temp->next->next;
                delete temp->next;
                temp->next = temp2;
            } else {
                throw "Out of range";
            }
        }
        void pop_front(){
            if(first != nullptr){
                SLL_element<T> * temp = first->next;
                delete first;
                first = temp;
            }
        }
        void pop_back(){
            if(first != nullptr){
                if(first->next == nullptr){
                    delete first;
                    first = nullptr;
                }
                SLL_element<T> * temp = first;
                while(temp->next->next != nullptr){
                    temp = temp->next;
                }
                delete temp->next;
                temp->next = nullptr;
            }
        }
        SLL_iterator<T> begin(){
            return SLL_iterator<T>(first);
        }
        SLL_iterator<T> end(){
            return SLL_iterator<T>(nullptr);
        }
    private:
        SLL_element<T> * first;
};
