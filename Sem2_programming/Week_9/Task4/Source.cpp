#include <iostream>
extern "C" int __fastcall  maxNotOversized(int);

void main()
{
	unsigned int a;
	std::cout << "Enter a = ";
	std::cin >> a;
	std::cout << "max({n | a^n less or equal 2^32 - 1}) = " << maxNotOversized(a) <<'\n';
	system("pause");
}
