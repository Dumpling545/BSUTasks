#include "flowerbed.h"
Flowerbed::Flowerbed(){}
std::ostream& operator<<(std::ostream &stream, const Flowerbed& flowerbed){
    stream << "   Flowerbed #" << flowerbed.id << std::endl;
    stream << "      Shape: " << flowerbed.shape <<std::endl;
    stream << "      Flowers:" <<std::endl;
    for(std::set<std::string>::iterator it = flowerbed.flowers.begin(); it != flowerbed.flowers.end(); it++){
        stream << "         •"<<(*it)<<std::endl;
    }
    if(flowerbed.flowers.size() == 0){
        stream << "          <no flowers>"<<std::endl;
    }
    stream << std::endl;
    return stream;
}

std::istream& operator>>(std::istream& stream, Flowerbed& flowerbed){
    std::string line;
    std::ws(stream);
    std::getline(stream, line);
    std::stringstream str_stream;
    str_stream << line;
    str_stream >> flowerbed.id >> flowerbed.shape;
    std::string temp;
    flowerbed.flowers.clear();
    while(str_stream >> temp){
        flowerbed.flowers.insert(temp);
    }
    return stream;
}
