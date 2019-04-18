#include "../include/fishermaninfo.h"
FishermanInfo::FishermanInfo(Fisherman f){
    lastName = f.lastName;
    firstName = f.firstName;
    age = f.age;
    double w = 0;
    std::for_each(f.fish.begin(), f.fish.end(), [&w] (std::pair<std::string, double> p){
                  w+= p.second;
                  });
    totalWeight = w;
}
std::ostream& operator<<(std::ostream &stream, const FishermanInfo& f_info){
    stream << std::setw(18) << f_info.lastName << std::setw(14) << f_info.firstName << "|" << std::setw(8) << "age: " << f_info.age << " " <<std::setw(12) << "weight: " << f_info.totalWeight;
    return stream;
}
FishermanInfo::FishermanInfo(const FishermanInfo& fInfo){
    lastName = fInfo.lastName;
    firstName = fInfo.firstName;
    age = fInfo.age;
    totalWeight = fInfo.totalWeight;
}
