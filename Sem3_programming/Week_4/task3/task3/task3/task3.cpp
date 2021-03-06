#include "stdafx.h"
#include <iostream>
#include <functional>
#include <string>
#include <sstream>

void to_string(std::stringstream & ss, const char * separator){}

template<typename T, typename... Targs>
void to_string(std::stringstream & ss, const char * separator, T value, Targs... args)
{
	ss << separator << value;
	to_string(ss, separator, args...);
}
template<typename T, typename... Targs>
std::string to_string(const char * separator, T value, Targs... args) {
	std::stringstream ss;
	ss << value;
	to_string(ss, separator, args...);
	return ss.str();
}

int main()
{
	short s = 7;
	float f = 78.87;
	char c = '`';
	/*
	auto to_str_lambda = [](const char * separator, auto value, auto... args){
		std::stringstream ss;
		ss << value;
		to_string(ss, separator, args...);
		return ss.str();
	};
	std::cout << to_str_lambda("; ", 1, 0, 123.6, f, '0', s, c, "have a good day") << '\n';
	*/
	std::cout << to_string("; ", 1, 0, 123.6, f, '0', s, c, "have a good day") << '\n';
	system("pause");
	return 0;
}