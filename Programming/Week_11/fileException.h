#pragma once
#include <string>
#include<exception>
using namespace std;
class FileException : public exception {
    public:
        FileException(string filename){
            this->filename = filename;
        }
        const char * what () const throw ()
        {
            return ("Something wrong with file '" + filename + "'").c_str();
        }
        string filename;

};

