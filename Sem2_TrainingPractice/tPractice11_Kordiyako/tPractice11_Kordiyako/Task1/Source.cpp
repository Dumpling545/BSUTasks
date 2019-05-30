#include <iostream>
#include <cstring>
extern "C" void __fastcall  deleteOddSpaces(char* str, int length);
extern "C" int __fastcall  countWords(char* str, int length);

void main()
{

	char src[100] = "  I love   this amazing     language...     halp!   ";
	char *str = src;
	std::cout << "Before:\n";
	std::cout <<"<str>"<< str << "</str>\n";
	deleteOddSpaces(str, strlen(src));
	std::cout << "After:\n";
	std::cout << "<str>" << str << "</str>\n";
	std::cout << "Amount of words: " << countWords(str, strlen(src))<<'\n';
	system("pause");
}
