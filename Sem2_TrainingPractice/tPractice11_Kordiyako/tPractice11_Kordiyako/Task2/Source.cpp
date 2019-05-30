#include <iostream>
#include <cstring>
extern "C" void __fastcall  deleteTextBetweenSpaces(char* str, int length);
void main()
{

	char src[100] = "  I love (can't stand)   this (awful) amazing    language...     halp!    ";
	char *str = src;
	std::cout << "Before:\n";
	std::cout << "<str>" << str << "</str>\n";
	deleteTextBetweenSpaces(str, strlen(src));
	std::cout << "After:\n";
	std::cout << "<str>" << str << "</str>\n";
	system("pause");
}
