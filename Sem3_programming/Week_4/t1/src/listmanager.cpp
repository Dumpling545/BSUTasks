#include "listmethods.h"

ListManager::ListManager(std::list<int> * list){
    this->list = list;
}
void ListManager::nonSetAction(std::function<void(int)> func){
    for(int i = 0; i < list->size(); i++){
        func(list[i]);
    }
}
void ListManager::setAction(std::function<void(int&)> func){
    for(int i = 0; i < list->size(); i++){
        func(list[i]);
    }
}
void ListManager::aggregate(std::function<int(int)> func){
    int sum = 0;
    for(int i = 0; i < list->size(); i++){
        sum += func(list[i]);
    }
    return sum;
}
int ListManager::findFirst(std::function<bool(int)> func){
    int sum = 0;
    for(int i = 0; i < list->size(); i++){
        sum += func(list[i]);
    }
    return sum;
}
