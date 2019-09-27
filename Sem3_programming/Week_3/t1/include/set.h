#pragma once
#include <iostream>
#include <initializer_list>
#include <string>
#include <sstream>
template <class U>
class SetIterator;
template <class T>
class Set
{
    public:
        Set(){
            elements = new T[capacity];
        }

        Set(std::initializer_list<T> args){
            size = args.size();
            capacity = size * EXTEND_COEFFICIENT;
            elements = new T[capacity];
            typename std::initializer_list<T>::iterator it = args.begin();
            int c = 0;
            while(it != args.end()){
                elements[c] = *(it);
                ++c;
                ++it;
            }
        }

        Set(const Set& set){
            size = set.size;
            capacity = set.capacity;
            elements = new T[capacity];
            for(int i = 0; i < capacity; i++){
                elements[i] = set.elements[i];
            }
        }

        Set(Set&& set) {
            elements = nullptr;
            swap(set);
        }

        ~Set(){
            delete [] elements;
            elements = nullptr;
        }

        SetIterator<T> iterator(){
            SetIterator<T> it = SetIterator<T>(this);
            return it;
        }
        void add(T element){
            T one_item_range[1] = {element};
            addRange(one_item_range, 1);
        }
        void addRange(T * range, int n){
            bool is_in_list[n];
            int old_els = 0;
            for(int i = 0; i < n; i++){
                is_in_list[i] = contains(range[i]);
                if(is_in_list[i]) ++old_els;
            }
            checkAndSetCapacity(n - old_els);
            for(int i = 0; i < n; i++){
                if(!is_in_list[i]) elements[size++] = range[i];
            }
        }
        void remove(T element){
            int index;
            if(contains(element, index)){
                for(int i = index; i < size - 1; i++){
                    elements[i] = elements[i+1];
                }
                --size;
                checkAndSetCapacity();
            }
        }

        bool contains(T element) const{
            int a;
            return contains(element, a);
        }

        int getSize(){
            return size;
        }

        void clear(){
            size = 0;
            capacity = 1;
            delete [] elements;
            elements = new int[1];
        }

        void swap(Set & set){
            T * temp = elements;
            elements = set.elements;
            set.elements = temp;

            int temp_int = size;
            size = set.size;
            set.size = temp_int;

            temp_int = capacity;
            capacity = set.capacity;
            set.capacity = capacity;
        }

        friend std::ostream& operator<<(std::ostream &stream,
                                        const Set<T>& set){
            int s = set.size;
            if(s > 0){
                stream<<'{';
                for(int i = 0; i < s - 1; i++){
                    stream << set.elements[i] <<",  ";
                }
                stream << set.elements[s-1]<<'}';
            } else {
                stream<<"[empty]";
            }
            return stream;
        }

        friend std::istream& operator>>(std::istream& stream, Set& set){
            set.clear();
            std::string str;
            std::getline(stream, str);
            std::istringstream ss(str);
            T element;
            while(ss >> element){
                set.add(element);
            }
            return stream;
        }

        T& operator[](const int index) const{
            if(index < 0 || index >= size){
                throw "Error: index is out of the array";
            } else {
                return elements[index];
            }
        }

        Set& operator=(const Set& set){
            delete [] elements;
            size = set.size;
            capacity = set.capacity;
            elements = new T[capacity];
            for(int i = 0; i < capacity; i++){
                elements[i] = set.elements[i];
            }
            return (*this);
        }

        Set& operator=(Set&& set){
            delete [] elements;
        	elements = nullptr;
            size = 0;
            capacity = 1;
            swap(set);
            return (*this);
        }

        const bool operator==(const Set& set) const{
            return contains(set) && set.contains(*(this));
        }

        const bool operator!=(const Set& set) const{
            return !(*(this) == set);
        }

        const Set operator+(const Set& set) const{
            Set result = *(this);
            result.addRange(set.elements, set.size);
            return result;
        }

        Set& operator+=(const Set& set){
            *(this) = *(this) + set;
            return *(this);
        }

        const Set operator-(const Set& set) const{
            Set result = *(this);
            for(int i = 0; i < set.size; i++){
                result.remove(set.elements[i]);
            }
            return result;
        }

        Set& operator-=(const Set& set){
            *(this) = *(this) - set;
            return *(this);
        }

		const Set operator*(const Set& set) const{
            Set a_without_b = *(this) - set;
            Set result = *(this) - a_without_b;
            return result;
		}

		Set& operator*=(const Set& set){
            *(this) = *(this) * set;
            return *(this);
		}
    protected:
        const int EXTEND_COEFFICIENT = 2;
        const int EXTEND_FLAG = 0;
        const int REDUCE_FLAG = 1;

        T * elements = nullptr;
        int size = 0;
        int capacity = 1;

        bool contains(T element, int &firstIndex) const{
            bool result = false;
            for(int i = 0; i < size; i++){
                if(elements[i] == element){
                    firstIndex = i;
                    result = true;
                    break;
                }
            }
            return result;
        }

        bool contains(const Set& set) const{
            bool result = true;
            for(int i = 0; i < set.size; i++){
                if(!contains(set.elements[i])){
                    result = false;
                    break;
                }
            }
            return result;
        }

        void checkAndSetCapacity(int change = 0){
            if(size + change > capacity){
                setCapacity(EXTEND_FLAG);
            } else if(size < capacity / EXTEND_COEFFICIENT){
                setCapacity(REDUCE_FLAG);
            }
        }

        void setCapacity(int flag){
            T * temp = nullptr;
            if(flag == EXTEND_FLAG){
                temp = new T[capacity *= EXTEND_COEFFICIENT];
            } else if(flag == REDUCE_FLAG){
                temp = new T[capacity /= EXTEND_COEFFICIENT];
            } else {
                return;
            }
            for(int i = 0; i < size; i++){
                temp[i] = elements[i];
            }
            delete [] elements;
            elements = temp;
        }

        template<class U> friend class SetIterator;
};
