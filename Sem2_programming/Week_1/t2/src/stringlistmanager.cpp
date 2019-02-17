#include "stringlistmanager.h"
#include <iostream>
#include <string>
#include <algorithm>
StringListManager::StringListManager(list<string> * clist)
{
    this->clist = clist;
}
void StringListManager::print(){
     for (std::list<string>::iterator it = clist->begin(); it != clist->end(); ++it){
         std::cout << (*it) << " ";
     }
     std::cout << endl;
}
void StringListManager::printElementsStartWith(char c){
    std::list<string> elems = StringListManager::getElementsStartWith(c);
    for (std::list<string>::iterator it = elems.begin(); it != elems.end(); ++it){
         std::cout << (*it) << " ";
     }
     std::cout << endl;
}
std::list<string> StringListManager::getElementsStartWith(char c){
    std::list<string> elems;
    std::list<string>::iterator it_end = clist->end();
    std::list<string>::iterator it_start =find_if(clist->begin(), it_end, [c](string & s) {return s[0] == c;});
    while(it_start != it_end){
        elems.push_back(*it_start);
        it_start = find_if(++it_start, it_end, [c](string & s) {return s[0] == c;});
    }
    return elems;
}
void StringListManager::deleteElementsStartWith(char c){
    std::list<string>::iterator p1=find_if(clist->begin(), clist->end(), [c](const string & s) {return s[0] == c;});
    std::list<string>::iterator p2=find_if(p1, clist->end(), [c](const string & s) {return s[0] != c;});
    clist->erase(p1, p2);
}
