#pragma once
#include "fileException.h"
class NonExistFileException : public FileException {
    public:
        NonExistFileException(string filename) : FileException(filename){}
        const char * what () const throw ()
        {
            return ("File '" + filename+ "' doesn't exist!").c_str();
        }
};

