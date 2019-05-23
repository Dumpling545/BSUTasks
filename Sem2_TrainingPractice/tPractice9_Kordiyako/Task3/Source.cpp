#include <iostream>
extern "C" int __fastcall  computeX_fastcall(int a, int b);
extern "C" int __stdcall  computeX_stdcall(int a, int b);
extern "C" int __cdecl  computeX_cdecl(int a, int b);

extern "C" short int __fastcall  short_computeX_fastcall(short int a, short int b);


void main()
{
	int a, b;
	short int c, d;
	std::cout << "Enter a: " << std::endl;
	std::cin >> a;
	std::cout << "Enter b: " << std::endl;
	std::cin >> b;
	std::cout << "Computing x: " << std::endl;
	std::cout << "	by fastcall method: " << computeX_fastcall(a, b) << std::endl;
	std::cout << "	by stdcall method: " << computeX_stdcall(a, b) << std::endl;
	std::cout << "	by cdecl method: " << computeX_cdecl(a, b) << std::endl;
	std::cout << "	by [SHORT] fastcall method: " << short_computeX_fastcall((short int)a, (short int)b) << std::endl;
	system("pause");
}
