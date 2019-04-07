#pragma once
#include <string>
#include <iostream>
class StudyClass
{
    public:
        StudyClass();
        std::string lectureHall;
        char type;
        std::string name;
        friend std::istream& operator>>(std::istream& stream, StudyClass& studyClass);

};
