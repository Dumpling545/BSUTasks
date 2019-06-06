#include <iostream>
#include <cstring>
extern "C" void __fastcall  deleteTextBetweenBrackets(char* str, int length);
void main()
{

	char src[200] = "123(345 (566) 2345) 8569)869  (876878)";
		//"()  I love (can't (stand)(t)hat)  this (awful) amazing    langu()age...     help!    ()";
	char *str = src;
	std::cout << "Before:\n";
	std::cout << "<str>" << str << "</str>\n";
	deleteTextBetweenBrackets(str, strlen(src));
	std::cout << "After:\n";
	std::cout << "<str>" << str << "</str>\n";
	system("pause");
}
