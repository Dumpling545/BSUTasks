#include <iostream>
#include <iomanip>
extern "C" float  __cdecl  find_root(float left, float right, float a, float b, float c);

void main()
{
	float left, right;
	std::cout << "Enter left, right: " << std::endl;
	std::cin >> left >> right;
	std::cout << "Enter a, b, c: " << std::endl;
	float a, b, c;
	std::cin >> a >> b >> c;
	float f = find_root(left, right, a, b, c);
	std::cout << "Compute root of x^3 +a*x^2 + b*x + c = 0: " << std::setprecision(12) << f << std::endl;
	system("pause");
}
