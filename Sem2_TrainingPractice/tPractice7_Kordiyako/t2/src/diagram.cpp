#include "diagram.h"

Diagram::Diagram(){}
void Diagram::addData(Fisherman fisherman){
    info.push_back(FishermanInfo(fisherman));
}
double Diagram::getMaxWeight(){
    std::vector<FishermanInfo>::iterator  maxWeightIt =  (
                    std::max_element(
                        info.begin(),
                        info.end(),
                        [](FishermanInfo f1, FishermanInfo f2){
                                return f1.totalWeight < f2.totalWeight;
                        })
                    );
    return (*maxWeightIt).totalWeight;
}
int Diagram::getMaxLastNameLengthIndex(){
    std::vector<FishermanInfo>::iterator  maxNameLengthIt =  (
        std::max_element(
            info.begin(),
            info.end(),
            [](FishermanInfo f1, FishermanInfo f2){
                    return f1.lastName.size() < f2.lastName.size();
            })
        );
    return (int)(maxNameLengthIt - info.begin());
}
double Diagram::getWeightSum(){
    double sum = 0;
    std::for_each(info.begin(), info.end(),
                  [&sum] (FishermanInfo f){
                   sum += f.totalWeight;
                   });
    return sum;
}
