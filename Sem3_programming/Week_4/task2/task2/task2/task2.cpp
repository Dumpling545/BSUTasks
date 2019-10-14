#include "stdafx.h"
#include <iostream>
#include <functional>

double sum()
{
	return 0;
}
template<typename T, typename... Targs>
double sum(T value, Targs... Fargs)
{
	double res = value;
	auto lambda = [Fargs...]() {return sum(Fargs...);};
	res += lambda();
	//res += sum(Fargs...);
	return res;
}

int main()
{
	short k = 1;
	std::cout << sum(1, 1, 0, 123.6, 1, '0', k) <<'\n';
	system("pause");
	return 0;
}