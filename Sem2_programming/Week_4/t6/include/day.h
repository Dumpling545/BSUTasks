#pragma once
#include <string>
#include "studyclass.h"
#include <vector>
class Day
{
    public:
        Day();
        std::string name;
        std::vector<StudyClass> classes;
        friend std::istream& operator>>(std::istream& stream, Day& day);
};
