#pragma once
#include <string>
using namespace std;
class Log{
public:
    Log();
    Log(string date, string message, string level);
    string date;
    string message;
    string level;
};
