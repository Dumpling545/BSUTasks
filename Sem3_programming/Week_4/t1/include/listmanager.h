#pragma once
#include <list>
#include <functional>
class ListManager
{
    public:
        ListManager(std::list<int> list);
        void nonValueNonSetAction(std::function<void(int)> func);
        int intNotSetAction(std::function<void(int)> func);
        void nonValueSetAction(std::function<void(int&)> func);
        sort(std::function<bool(int, int)> comparator);
    private:
        std::list<int> list;
};
