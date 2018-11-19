#include <iostream>
#include <math.h>

using namespace std;
/*
	Дано квадратное уравнение. Найти корни, в противном случае вывести соответствующее сообщение.

	Выполнил: Ян Кордияко

	Input			Output
	--------------------------------------------------------------------------
	-1 -2 -1		x = -1

	11.27 89 1		x1 = -7.88582
					x2 = -0.011252

	100.4 2.3 1.1	No root

	0 7.6 0.2		x = -0.0263158

	6 0 0.8			No root

	8.7 2.43 0		x1 = -0.27931
					x2 = 0

	0 0 3			No root

	0 0 0			x - any number
*/
void main() {
	//coefficients of equation
	double a = 0;
	double b = 0;
	double c = 0;
	//discriminant
	double d = 0;

	cout << "a*x^2 + b*x + c = 0" << endl;
	cout << "Enter a:" << endl;
	cin >> a;
	cout << "Enter b:" << endl;
	cin >> b;
	cout << "Enter c:" << endl;
	cin >> c;
	if(a != 0) {
		//discriminant computation
		d = b * b - 4 * a*c;

		if (d < 0) {
			cout << "No root" << endl;
		}
		else if (d == 0) {
			cout << "x = " << -b / (2.0 * a) << endl;
		}
		else {
			cout << "x1 = " << -(b + sqrt(d)) / (2.0*a) << endl;
			cout << "x2 = " << (-b + sqrt(d)) / (2.0*a) << endl;
		}
	}
	else {
		if (b != 0) {
			cout << "x = " << -c / b << endl;
		}
		else {
			if (c == 0) {
				cout << "x - any number" << endl;
			}
			else {
				cout << "No root" << endl;
			}
		}
	}
	system("pause");
}