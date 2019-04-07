#include "stringlistmanager.h"
#include <iostream>
#include <string>
#include <algorithm>
StringListManager::StringListManager(std::list<std::string> * clist)
{
    this->clist = clist;
}
void StringListManager::print(){
     for (std::list<std::string>::iterator it = clist->begin(); it != clist->end(); ++it){
         std::cout << (*it) << " ";
     }
     std::cout << std::endl;
}
void StringListManager::printElements(std::list<std::string> elems){
    for (std::list<std::string>::iterator it = elems.begin(); it != elems.end(); ++it){
         std::cout << (*it) << " ";
     }
     std::cout << std::endl;
}
std::list<std::string> StringListManager::getElementsStartWith(char c){
    std::list<std::string> elems;
    std::list<std::string>::iterator it_end = clist->end();
    std::list<std::string>::iterator it_start =find_if(clist->begin(), it_end, [c](std::string & s) {return s[0] == c;});
    while(it_start != it_end){
        elems.push_back(*it_start);
        it_start = find_if(++it_start, it_end, [c](std::string & s) {return s[0] == c;});
    }
    return elems;
}
void StringListManager::deleteElementsStartWith(char c){
    std::list<std::string>::iterator p1=find_if(clist->begin(), clist->end(), [c](const std::string & s) {return s[0] == c;});
    std::list<std::string>::iterator p2=find_if(p1, clist->end(), [c](const std::string & s) {return s[0] != c;});
    clist->erase(p1, p2);
}
