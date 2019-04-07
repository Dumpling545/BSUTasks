#pragma once
#include <string>
#include <list>
class StringListManager
{
    public:
        StringListManager(std::list<std::string> * clist);
        void print();
        std::list<std::string> getElementsStartWith(char c);
        void deleteElementsStartWith(char c);
        static void printElements(std::list<std::string> elems);
    private:
        std::list<std::string> * clist;
};
