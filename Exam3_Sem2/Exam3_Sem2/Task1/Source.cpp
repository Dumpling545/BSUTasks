#include <iostream>
/*	�������� ������� lcm, ������� ��������� ������������� ������ numbers � ��� ����� n (n ? 1), 
	� ���������� ���������� ����� ������� ���� ��������� �������.*/
extern "C" int __fastcall  lcm(int* ar, int n);
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
	int res;
	__asm {
		mov ecx, ar
		mov edx, n
		call lcm
		mov res, eax
	}
	std::cout << "\nLCM: " << res << std::endl;
	system("pause");
}
