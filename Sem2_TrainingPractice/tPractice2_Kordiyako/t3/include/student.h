#pragma once
#include <cstring>
#include <iostream>
class Student
{
    public:
        Student();
        char name[20];
        int group;
        double mark;
        friend std::istream& operator>>(std::istream& stream, Student& student);
};
