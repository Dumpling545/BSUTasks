#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<utility>
#include "../include/fisherman.h"
class FileManager
{
    public:
        static bool checkInput(std::ifstream &ifs);
    private:
        FileManager();
};
