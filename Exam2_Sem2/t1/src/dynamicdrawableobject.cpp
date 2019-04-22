#include "../include/dynamicdrawableobject.h"

DynamicDrawableObject::DynamicDrawableObject()
{
    //ctor
}

void DynamicDrawableObject::move(int dx, int dy){
    std::map<int, DrawableItem*>::iterator it;
    for(it = items.begin(); it!= items.end(); it++){
        DrawableItem * item = (*it).second;
        if(item->isDynamic()){
            ((DynamicDrawableItem*)item)->move(dx, dy);
        }
    }
}
