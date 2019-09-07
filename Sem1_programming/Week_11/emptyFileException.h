#pragma once
#include "fileException.h"
class EmptyFileException : public FileException {
    public:
        EmptyFileException(string filename) : FileException(filename){}
        const char * what () const throw ()
        {
            return ("File '" + filename +"' is empty!").c_str();
        }
};
