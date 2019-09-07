#pragma once
#include<string>
#include<iostream>
using namespace std;
class HMTime
{
private:
    int minutes = 0;
    //HMTime(int hours, int minutes);
public:
    HMTime();
    HMTime(const HMTime& time);
    HMTime(string str);
    string get() const;
    int inMinutes() const;
};
