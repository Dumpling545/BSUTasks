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
SIZE Diagram::getMaxLastNameSize(HDC &hdc){
    SIZE result;
    std::vector<FishermanInfo>::iterator  maxNameLengthIt =  (
        std::max_element(
            info.begin(),
            info.end(),
            [](FishermanInfo f1, FishermanInfo f2){
                    return f1.lastName.size() < f2.lastName.size();
            })
        );
    std::string mLastName = (*maxNameLengthIt).lastName;
    GetTextExtentPoint32(hdc, _T(mLastName.c_str()), mLastName.size() +
                         SIGNATURE_PRECISION + 6, &result);
    return result;
}
double Diagram::getWeightSum(){
    double sum = 0;
    std::for_each(info.begin(), info.end(),
                  [&sum] (FishermanInfo f){
                   sum += f.totalWeight;
                   });
    return sum;
}
