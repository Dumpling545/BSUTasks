#include <iostream>
extern "C" int __fastcall  uniqueElements(int*, int);
extern "C" int __fastcall  mostFrequentElement(int*, int);
void main()
{
	int n = 16;
	int * ar = new int[n]{ 1, 4, 4, 2, 3, 0, 3, 1, 3, 4, 4, 5, 1, 5, 1, 4};
	int unique = uniqueElements(ar, n);
	std::cout << "Amount of unique elements: " << unique << std::endl;
	int mostFrequent = mostFrequentElement(ar, n);
	std::cout << "Most frequent element (first left if > 1): " <<  mostFrequent << std::endl;
	system("pause");
}
