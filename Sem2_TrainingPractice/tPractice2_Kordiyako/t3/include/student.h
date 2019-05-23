#pragma once
#include <cstring>
#include <iostream>
#include <iomanip>
class Student
{
    public:
        Student();
        char name[20];
        int group;
        double mark;
        friend std::istream& operator>>(std::istream& stream, Student& student);
        friend std::ostream& operator<<(std::ostream& stream,
                                        const Student& student);
};
