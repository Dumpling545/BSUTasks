#pragma once
#include <exception>
using namespace std;
class InvalidCommandException : public exception{
    const char * what () const throw ()
    {
    	return "Invalid command!";
    }
};
