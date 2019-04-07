#include "studyclass.h"

StudyClass::StudyClass()
{
    //ctor
}
std::istream& operator>>(std::istream& stream, StudyClass& studyClass){
    stream >> studyClass.type;
    switch(studyClass.type){
        case 'н':
            studyClass.name="";
            studyClass.lectureHall =  "";
            break;
        case 'ф':
            studyClass.name = "‘изкультура";
            studyClass.lectureHall =  "зал";
            break;
        case 'п':
        case 'л':
            stream >> studyClass.name >> studyClass.lectureHall;
            break;
    }
    return stream;
}
