#include <iostream>
using namespace std;
/*
	Пользователь вводит четыре числа. Найдите наибольшее четное число среди них. Если оно не существует, выведите фразу "not found".

	Выполнил: Ян Кордияко

	Input			Output
	--------------------------------------------------------------------------
	1 3 5 7			Not found

	-2 5 7 1		-2

	-8 -6 -4 -2		-2

	1 2 4 4			4
*/
void main() {
	//numbers
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	cout << "Enter a:" << endl;
	cin >> a;
	cout << "Enter b:" << endl;
	cin >> b;
	cout << "Enter c:" << endl;
	cin >> c;
	cout << "Enter d:" << endl;
	cin >> d;

	if (a % 2 != 0 && b % 2 != 0 && c % 2 != 0 && d % 2 != 0) {
		cout << "Not found" << endl;
	}
	else if (a % 2 == 0 && (b % 2 != 0 || a >= b) && (c % 2 != 0 || a >= c) && (d % 2 != 0 || a >= d)) {
		cout << "Biggest even: " << a << endl;
	}
	else if (b % 2 == 0 && (a % 2 != 0 || b >= a) && (c % 2 != 0 || b >= c) && (d % 2 != 0 || b >= d)) {
		cout << "Biggest even: " << b << endl;
	}
	else if (c % 2 == 0 && (b % 2 != 0 || c >= b) && (a % 2 != 0 || c >= a) && (d % 2 != 0 || c >= d)) {
		cout << "Biggest even: " << c << endl;
	}
	else if (d % 2 == 0 && (b % 2 != 0 || d >= b) && (c % 2 != 0 || d >= c) && (a % 2 != 0 || d >= a)) {
		cout << "Biggest even: " << d << endl;
	}
	system("pause");
}