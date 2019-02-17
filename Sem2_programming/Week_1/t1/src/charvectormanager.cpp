#include "charvectormanager.h"
CharVectorManager::CharVectorManager(Vector<char> * vector){
    this->vector = vector;
}
void CharVectorManager::print(){
    VectorIterator<char> iterator(vector);
    iterator.toBegin();
    do{
        cout << (char)iterator << ' ';
    }while(!(iterator++).isEnd());
    cout << '\n' << endl;
}
void CharVectorManager::printReverse(){
    VectorIterator<char> iterator(vector);
    iterator.toEnd();
    do{
        cout << (char)iterator << ' ';
    }while(!(iterator--).isBegin());
    cout << '\n' << endl;
}
