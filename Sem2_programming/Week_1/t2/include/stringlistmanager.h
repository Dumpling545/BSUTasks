#pragma once
#include <string>
#include <list>
using namespace std;
class StringListManager
{
    public:
        StringListManager(list<string> * clist);
        void print();
        list<string> getElementsStartWith(char c);
        void deleteElementsStartWith(char c);
        void printElementsStartWith(char c);
    private:
        list<string> * clist;
};
