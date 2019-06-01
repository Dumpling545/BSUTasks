#include <iostream>
#include <iomanip>
extern "C" void __cdecl  swap(int** matrix, int n, int i);
extern "C" void __fastcall  switchColumnExtrema(int** matrix, int n);
void main()
{
	int n;
	std::cout << "Enter matrix size: \n";
	std::cin >> n;
	int** matrix = new int*[n];
	std::cout << "Enter matrix: \n";
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
		for (int j = 0; j < n; j++) {
			std::cin >> matrix[i][j];
		}
	}
	int index;
	std::cout << "Enter i: \n";
	std::cin >> index;
	index--;

	/*swap(matrix, n, index);

	std::cout << "Matrix after swap: \n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << std::setw(3) << matrix[i][j] << " ";
		}
		std::cout << '\n';
	}*/
	switchColumnExtrema(matrix, n);
	std::cout << "Matrix after switching column extrema: \n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << std::setw(3) << matrix[i][j] << " ";
		}
		std::cout << '\n';
	}
	system("pause");
}
