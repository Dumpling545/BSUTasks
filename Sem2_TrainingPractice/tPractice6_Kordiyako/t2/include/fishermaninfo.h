#pragma once
#include "fisherman.h"
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <map>
class FishermanInfo
{
    public:
        FishermanInfo(Fisherman f);
        FishermanInfo(const FishermanInfo& fInfo);
        std::string firstName;
        std::string lastName;
        int age;
        double totalWeight;
        friend std::ostream& operator<<(std::ostream &stream, const FishermanInfo& f_info);
};
