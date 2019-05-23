#include <iostream>
extern "C" int __fastcall  Compute(int);

void main()
{
	int a;
	std::cout << "Enter a:";
	std::cin >> a;
	std::cout << "a^5 + a^3 + a^1 = " << Compute(a) << std::endl;
	system("pause");
}
