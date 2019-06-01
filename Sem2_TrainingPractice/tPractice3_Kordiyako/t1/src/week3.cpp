#include "week3.h"
bool setStringComparator::operator()(const std::set<std::string> &a,
                                     const std::set<std::string> &b)const{
    int a_length = a.size();
    int b_length = b.size();
    std::set<std::string>::iterator a_it  = a.begin();
    std::set<std::string>::iterator b_it = b.begin();
    bool result = a_length < b_length;
    for(int i = 0; i < std::min(a_length, b_length); i++){
        std::string a_str = *a_it;
        std::string b_str = *b_it;
        if(a_str == b_str){
            a_it++;
            b_it++;
        } else {
            result = a_str < b_str;
            break;
        }
    }
    return result;
}
bool isCorrectInputFile(std::ifstream &_fin){
    bool res = true;
    if(!_fin){
        std::cout << "Input file doesn't exist" << std::endl;
        res =  false;
    } else if(_fin.peek() == std::ifstream::traits_type::eof()){
        std::cout << "Input file is empty" << std::endl;
        res = false;
    }
    return res;
}
void sortByShape(std::list<Flowerbed> & flowerbeds){
    flowerbeds.sort([](Flowerbed f1, Flowerbed f2){
                    return f1.shape < f2.shape;
                    });
}

void convertListToMap(std::list<Flowerbed> src,  std::map<int, Flowerbed> & dest){
    for(std::list<Flowerbed>::iterator it = src.begin(); it != src.end(); it++){
        dest[(*it).id] = *it;
    }
}

void getUniqueShapes(std::map<int, Flowerbed> flowerbeds,
                     std::set<std::string> & shapes){
    std::transform(flowerbeds.begin(), flowerbeds.end(),
              inserter(shapes, shapes.begin()),
              [](std::pair<int, Flowerbed> p) { return p.second.shape;});
}
