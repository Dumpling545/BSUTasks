#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "fileException.h"
#include "emptyFileException.h"
#include "nonExistFileException.h"
#include "logger.h"
using namespace std;
class FileManager{
    public:
        FileManager();
        vector<string> read(string filename);
        void write(string filename, string text);
    private:
        ifstream fin;
        ofstream fout;
        void openInputFile(string fileName);
        void openOutputFile(string fileName);
};
