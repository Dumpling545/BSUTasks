#pragma once
#include <list>
#include <functional>
/**
    вывода элементов списка;
    сортировки элементов списка по модулю значений;
    поиска первого четного числа;
    вычисления количества четных чисел с использованием for_each;
    замены каждого отрицательного числа на ноль.
*/
class ListManager
{
    public:
        ListManager(std::list<int> * list);
        void nonSetAction(std::function<void(int)> func);
        void setAction(std::function<void(int&)> func);
        int aggregate(std::function<int(int)> func);
        int findFirst(std::function<bool(int)> func);
        void sort(std::function<bool(int, int)> comparator);
    private:
        std::list<int> * list = nullptr;
};
