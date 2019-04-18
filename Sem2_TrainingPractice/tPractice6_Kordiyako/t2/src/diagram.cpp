#include "diagram.h"

Diagram::Diagram(){}
void Diagram::addData(Fisherman fisherman){
    info.push_back(FishermanInfo(fisherman));
}
