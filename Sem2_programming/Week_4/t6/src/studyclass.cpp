#include "studyclass.h"

StudyClass::StudyClass()
{
    //ctor
}
std::istream& operator>>(std::istream& stream, StudyClass& studyClass){
    stream >> studyClass.type;
    switch(studyClass.type){
        case '�':
            studyClass.name="";
            studyClass.lectureHall =  "";
            break;
        case '�':
            studyClass.name = "�����������";
            studyClass.lectureHall =  "���";
            break;
        case '�':
        case '�':
            stream >> studyClass.name >> studyClass.lectureHall;
            break;
    }
    return stream;
}
