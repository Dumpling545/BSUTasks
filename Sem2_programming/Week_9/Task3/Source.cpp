#include <iostream>
extern "C" bool __fastcall  isSolution(int, int);

void main()
{
	std::cout << "2x + 3y = 50"<< '\n' << "Solutions:" << '\n';
	int c = 0;
	for (int x = 1; x <= 50; x++) {
		for (int y = 1; y <= 50; y++) {
			if (isSolution(x, y)) {
				std::cout <<"x = " <<  x << ", y = " << y << " " << '\n';
				c++;
			}
		}
	}
	std::cout << "Amount: " << c;
	system("pause");
}
