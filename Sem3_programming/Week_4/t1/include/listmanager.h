#pragma once
#include <list>
#include <functional>
/**
    ������ ��������� ������;
    ���������� ��������� ������ �� ������ ��������;
    ������ ������� ������� �����;
    ���������� ���������� ������ ����� � �������������� for_each;
    ������ ������� �������������� ����� �� ����.
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
