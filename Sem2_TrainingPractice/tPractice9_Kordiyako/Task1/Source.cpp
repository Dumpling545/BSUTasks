#include <iostream>
extern "C" void __fastcall  swapWords_fastcall(char*&, char*&);
extern "C" void __stdcall  swapWords_stdcall(char*&, char*&);
extern "C" void __cdecl  swapWords_cdecl(char*&, char*&);

void main()
{
	char *s1 = (char*)"[First word]";
	char *s2 = (char*)"[Second word]";
	std::cout << "WORDS: " << s1 << " " << s2 << std::endl;
	swapWords_fastcall(s1, s2);
	std::cout << "AFTER METHOD swapWords_fastcall: " << s1 <<" " << s2 << std::endl;
	swapWords_stdcall(s1, s2);
	std::cout << "AFTER METHOD swapWords_stdcall: " << s1 << " " << s2 << std::endl;
	swapWords_cdecl(s1, s2);
	std::cout << "AFTER METHOD swapWords_cdecl: " << s1 << " " << s2 << std::endl;
	system("pause");
}
