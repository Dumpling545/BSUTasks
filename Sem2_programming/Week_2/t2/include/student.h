#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<iterator>
class Student
{
    public:
        std::string name;
        int group;
        std::vector<int> examsResult;
        friend std::ostream& operator<<(std::ostream &stream, const Student& student);
        friend std::istream& operator>>(std::istream& stream, Student& student);
};
