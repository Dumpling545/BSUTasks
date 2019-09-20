#pragma once
template <class T>
class Set;
template <class U>
class SetIterator
{
    public:
        SetIterator(Set<U> *set) {
            this->set = set;
        }
        void next(){
            index++;
        }
         bool hasNext(){
            return (index < set->size);
        }
        U& current() {
            return set->elements[index];
        }
    private:
        SetIterator() {}
         Set<U>*  set;
        int index = 0;
};
