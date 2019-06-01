#include <iostream>
extern "C" bool __fastcall  isPalindrome(int*, int);

void main()
{
	int n;
	std::cout << "Enter n:\n";
	std::cin >> n;
	int * ar = new int[n];
	std::cout << "Enter array:\n";
	for (int i = 0; i < n; i++) {
		std::cin >> ar[i];
	}
	bool p = isPalindrome(ar, n);
	std::cout << "Array is " << (p ? " " : "not ")<< "a palindrome"<< std::endl;
	system("pause");
}
