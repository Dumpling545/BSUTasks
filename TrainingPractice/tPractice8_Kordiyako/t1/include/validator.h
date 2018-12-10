#pragma once
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
class Validator
{
    public:
        static bool validateFileName(const string filename);
        static bool validateInputStream(ifstream &is);
        static bool validateOrder(int order);
    private:
        Validator();
};
