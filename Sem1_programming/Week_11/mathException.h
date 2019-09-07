#pragma once
#include<exception>
using namespace std;
class MathException : public exception {
    public:
        const char * what () const throw ()
        {
            return "Division by zero";
        }
};
