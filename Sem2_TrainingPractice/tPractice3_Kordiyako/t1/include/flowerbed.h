#pragma once
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
class Flowerbed
{
    public:
        Flowerbed();
        int id;
        std::string shape;
        std::set<std::string> flowers;
        friend std::ostream& operator<<(std::ostream &stream, const Flowerbed& flowerbed);
        friend std::istream& operator>>(std::istream& stream, Flowerbed& flowerbed);

};
