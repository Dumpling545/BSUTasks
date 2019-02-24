#pragma once
#include<string>
#include<iostream>
class BusRouteInfo
{
    public:
        unsigned int routeNumber;
        std::string driver;
        unsigned int busNumber;
        std::string busBrand;
        friend std::ostream& operator<<(std::ostream &stream, const BusRouteInfo& route);
        friend std::istream& operator>>(std::istream& stream, BusRouteInfo& route);
};
