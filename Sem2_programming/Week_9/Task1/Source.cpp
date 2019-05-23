#include <iostream>
extern "C" int __fastcall  Sum(int, int);
extern "C" int __fastcall  Subtraction(int, int);
extern "C" int __fastcall  Multiplication(int, int);
extern "C" int __fastcall  Division(int, int);
extern "C" int __fastcall  Remainder(int, int);

void main()
{
	int param1 = -9;
	int param2 = 7;
	std::cout << "Param 1: " << param1 << ", Param 2: " << param2 << std::endl;
	std::cout << "sum = " << Sum(param1, param2) << std::endl;
	std::cout << "subtract = " << Subtraction(param1, param2) << std::endl;
	std::cout << "multiplication = " << Multiplication(param1, param2) << std::endl;
	std::cout << "division = " << Division(param1, param2) << std::endl;
	std::cout << "remainder = " << Remainder(param1, param2) << std::endl;
	system("pause");
}
