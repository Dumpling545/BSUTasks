#include "../include/busrouteinfo.h"
std::ostream& operator<<(std::ostream &stream, const BusRouteInfo& route){
    stream << route.routeNumber << ' ' << route.driver << ' ' << route.busNumber << ' ' << route.busBrand;
    return stream;
}

std::istream& operator>>(std::istream& stream, BusRouteInfo& route){
    stream >> route.routeNumber >>  route.driver >> route.busNumber >>  route.busBrand;
    return stream;
}
