#include <iostream>
#include <iomanip>
/*
	�������� ������� shift, ������� ��������� ������������� ������� matrix, 
	� ������� � ���������� ����� n (n >= 1), ���������� �������� m (m >= 1); 
	� ����� ��������������� ����� k. ������� ������ ���������� �������� ������ 
	�� k ������� ��� �������� ���������� �������. 
*/
extern "C" void __cdecl  shift(int ** matrix, int n, int m, unsigned int k);

void main()
{
	int n, m, k;
	std::cout << "Enter n:\n";
	std::cin >> n;
	int ** mtrx = new int*[n];
	std::cout << "Enter m:\n";
	std::cin >> m;
	std::cout << "Enter matrix:\n";
	for (int i = 0; i < n; i++) {
		mtrx[i] = new int[m];
		for (int j = 0; j < m; j++) {
			std::cin >> mtrx[i][j];
		}
	}
	std::cout << "Enter k(shift):\n";
	std::cin >> k;
	shift(mtrx, n, m, k);
	std::cout << "Result:\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout <<std::setw(5) << mtrx[i][j] << ' ';
		}
		std::cout << '\n';
	}
	system("pause");
}
