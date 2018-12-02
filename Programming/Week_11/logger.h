#pragma once
#include <fstream>
#include "log.h"
using namespace std;
class Logger{
    public:
        static void info(string message);
        static void warning(string message);
    private:
        ofstream fout;
};
