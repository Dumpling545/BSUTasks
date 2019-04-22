#include "../include/drawableobject.h"

DrawableObject::DrawableObject()
{
}

DrawableObject::~DrawableObject()
{
    std::map<int, DrawableItem*>::iterator it;
    for(it = items.begin(); it!= items.end(); it++){
        delete (*it).second;
    }
    items.clear();
}

RECT DrawableObject::border(){
    RECT rect, temp_rect;
    if(items.size() > 0){
        std::map<int, DrawableItem*>::iterator it;
        rect = (*(items.begin())).second->border();
        for(it = ++items.begin(); it!= items.end(); it++){
            temp_rect = (*it).second->border();
            UnionRect(&rect, &temp_rect, &rect);
        }
    }
    return rect;
}

void DrawableObject::draw(HDC &hdc){
    std::map<int, DrawableItem*>::iterator it;
    for(it = items.begin(); it!= items.end(); it++){
        (*it).second->draw(hdc);
    }
}
