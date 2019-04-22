#include "../include/fisherman.h"
Fisherman::Fisherman(){}

std::istream& operator>>(std::istream& stream, Fisherman& fisherman){
    std::string line;
    std::ws(stream);
    std::getline(stream, line);
    std::stringstream str_stream;
    str_stream << line;
    str_stream >> fisherman.lastName >> fisherman.firstName >> fisherman.age;
     std::ws(stream);
    line ="";
    std::getline(stream, line);
    str_stream.clear();
    str_stream << line;
    std::string temp;
    double weight;
    fisherman.fish.clear();
    while(str_stream >> temp >> weight){
        fisherman.fish.insert(std::make_pair(temp, weight));
    }
    return stream;
}
