#pragma once
#include "invalidCommandException.h"
using namespace std;
class UndefinedArgumentException : public InvalidCommandException{
    const char * what () const throw ()
    {
    	return "Missing required argument!";
    }
};
