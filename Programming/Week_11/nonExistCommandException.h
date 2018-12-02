#pragma once
#include "invalidCommandException.h"
using namespace std;
class NonExistCommandException : public InvalidCommandException{
    const char * what () const throw ()
    {
    	return "Command doesn't exist!";
    }
};
