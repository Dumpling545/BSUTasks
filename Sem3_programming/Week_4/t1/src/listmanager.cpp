#include "listmethods.h"

ListManager::ListManager(std::list<int> list){
    this->list = list;
}
ListManager::nonValueNonSetAction(std::function<void(int)> fun){
    this->list = list;
}
