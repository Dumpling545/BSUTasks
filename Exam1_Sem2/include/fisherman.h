#pragma once
#include<string>
#include<map>
#include<iostream>
#include<sstream>
#include<utility>
class Fisherman
{
    public:
        Fisherman();
        std::string firstName;
        std::string lastName;
        std::multimap<std::string, double> fish;
        friend std::istream& operator>>(std::istream& stream, Fisherman& fishermen);
        int age;

};
