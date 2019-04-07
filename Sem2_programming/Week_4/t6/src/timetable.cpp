
#include "timetable.h"

Timetable::Timetable()
{
    //ctor
}
int Timetable::getClassesMaxCount(){
    int res = 0;
    for(int i = 0; i < days.size(); i++){
        if(days[i].classes.size() > res){
            res = days[i].classes.size();
        }
    }
    return res;
}
std::istream& operator>>(std::istream& stream, Timetable& timetable){
    std::string line;
    std::ws(stream);
    Day day;
    while(std::getline(stream, line)){
        std::stringstream str_stream;
        str_stream << line;
        str_stream >> day;
        std::ws(stream);
        timetable.days.push_back(day);
    }
    return stream;
}
bool Timetable::isEmpty(){
    return days.size() == 0;
}
