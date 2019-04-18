#include "vector.h"
template <class T>
class Vectorex : public Vector<T>{
    public:
        Vectorex() : Vector<T>() {}
        Vectorex(const Vector<T> & source) : Vector<T>(source) {}
        Vectorex(int defSize, T fillWith) : Vector<T>(defSize, fillWith) {}
        void push_front(T element){
            if(this->size >= this->capacity) this->recapacity(this->size*2);
            for(int i = this->size; i > 0; i--){
                this->elements[i] = this->elements[i-1];
            }
            this->elements[0] = element;
            this->size++;
        }
};
