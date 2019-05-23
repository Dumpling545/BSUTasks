#include <iostream>
extern "C" int __cdecl  multiplyMatrices(int** mleft, int** mright, int ** result, int n, int m, int k);

void main()
{
	int n, m, k;
	std::cout << "Enter n, m, k for matrix multiplication LEFT[n x m]*RIGHT[m x k]: \n";
	std::cin >> n >> m >> k;
	int** matrixleft = new int*[n];
	int** matrixright = new int*[m];
	int** matrix_result = new int*[n];
	std::cout << "Enter matrix LEFT[n x m]: \n";
	for (int i = 0; i < n; i++) {
		matrixleft[i] = new int[n];
		for (int j = 0; j < m; j++) {
			std::cin >> matrixleft[i][j];
		}
	}
	std::cout << "Enter matrix RIGHT[m x k]: \n";
	for (int i = 0; i < m; i++) {
		matrixright[i] = new int[n];
		for (int j = 0; j < k; j++) {
			std::cin >> matrixright[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		matrix_result[i] = new int[k];
		for (int j = 0; j < k; j++) {
			matrix_result[i][j] = 0;
		}
	}
	multiplyMatrices(matrixleft, matrixright, matrix_result, n, m, k);
	system("pause");
}
