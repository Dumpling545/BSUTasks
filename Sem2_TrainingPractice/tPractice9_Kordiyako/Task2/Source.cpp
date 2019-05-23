#include <iostream>
extern "C" void __cdecl  solveEquation(int a, int b, int &state, int& x);
const int NO_SOLUTION = 0;
const int ONE_SOLUTION = 1;
const int INF_SOLUTIONS = 2;
void main()
{
	std::cout << "Equation: ax = b\n";
	int a, b, x, state;
	std::cout << "Enter 'a':\n";
	std::cin >> a;
	std::cout << "Enter 'b':\n";
	std::cin >> b;
	solveEquation(a, b, state, x);
	if (state == NO_SOLUTION) {
		std::cout << "No solutions\n";
	}
	else if (state == ONE_SOLUTION) {
		std::cout << "Solution: x = " << x << '\n';
	}
	else if (state == INF_SOLUTIONS) {
		std::cout << "Infinitely many solutions\n";
	} 
	system("pause");
}
