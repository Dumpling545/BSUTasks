#pragma once
#include<exception>
#include<string>
using namespace std;
class InvalidOperationException : public exception {
	public:
		InvalidOperationException(string operation){
			this->operation = operation;
		}
		const char * what () const throw ()
		{
			return ("Invalid operation: " + operation).c_str();
		}
		string operation;
};
