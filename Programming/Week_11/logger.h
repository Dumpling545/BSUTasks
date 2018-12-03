#pragma once
#include <fstream>
#include <ctime>
#include "log.h"
using namespace std;
class Logger{
    public:
        static void info(string message);
        static void warning(string message);
        static void start();
    private:
        static void save(Log log);
};
