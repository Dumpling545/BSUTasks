#include <iostream>
extern "C" bool __fastcall  isPalindrome(int*, int);

void main()
{
	int n = 9;
	int * ar = new int[n] { 1, 2, 3, 4, 5, 4, 3, 2, 0};
	bool p = isPalindrome(ar, n);
	std::cout << "Array 'ar' is " << (p ? " " : "not ")<< "a palindrome"<< std::endl;
	system("pause");
}
