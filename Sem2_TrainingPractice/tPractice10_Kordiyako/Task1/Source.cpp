#include <iostream>
extern "C" int __fastcall  uniqueElements(int*, int);
extern "C" int __fastcall  mostFrequentElement(int*, int);
void main()
{
	int n;
	std::cout << "Enter n:\n";
	std::cin >> n;
	int * ar = new int[n];
	std::cout << "Enter array:\n";
	for(int i = 0; i < n; i++){
		std::cin >> ar[i];
	}
	int unique = uniqueElements(ar, n);
	std::cout << "Amount of unique elements: " << unique << std::endl;
	int mostFrequent = mostFrequentElement(ar, n);
	std::cout << "Most frequent element (first left if many most frequent): " <<  mostFrequent << std::endl;
	system("pause");
}
