#include "day.h"

Day::Day()
{
    //ctor
}
std::istream& operator>>(std::istream& stream, Day& day){
    stream >> day.name;
    day.classes.clear();
    StudyClass studyclass;
    while(stream >> studyclass){
        day.classes.push_back(studyclass);
    }
    return stream;
}
