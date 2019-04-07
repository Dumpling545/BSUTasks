#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include "day.h"
class Timetable
{
    public:
        Timetable();
        std::vector<Day> days;
        int getClassesMaxCount();
        bool isEmpty();
        friend std::istream& operator>>(std::istream& stream, Timetable &timetable);
};
