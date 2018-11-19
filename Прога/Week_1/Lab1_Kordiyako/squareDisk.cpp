/*
	Известны площадь квадрата и площадь круга. Определить:
	уместится ли квадрат в круге;
	уместится ли круг в квадрате.

	Выполнил: Ян Кордияко

	Input		Output
	--------------------------------------------------------------------------
	100	78.5	You can place disk with area 78.5 into square with area 100 
				You cannot place square with area 100 into disk with area 78.5

	100 80		You cannot place disk with area 80 into square with area 100
				You cannot place square with area 100 into disk with area 80

	-100		Area of square must be positive. Please re-enter:

	100 0		Area of disk must be positive. Please re-enter:

	100 200		You cannot place disk with area 200 into square with area 100
				You can place square with area 100 into disk with area 200

*/


#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

void main() {
	//s - area of square
	double s = 0;
	//s - area of disk
	double d = 0;
	cout << "Enter area of square:" << endl;
	cin >> s;
	while (s <= 0) {
		cout << "Area of square must be positive. Please re-enter: " << endl;
		cin >> s;
	}
	cout << "Enter area of disk:" << endl;
	cin >> d;
	while (d <= 0) {
		cout << "Area of disk must be positive. Please re-enter: " << endl;
		cin >> d;
	}
	if (d * 4.0 / M_PI <= s) {
		cout << "You can place disk with area " << d << " into square with area " << s << endl;
	}
	else {
		cout << "You cannot place disk with area " << d << " into square with area " << s << endl;
	}
	if (d * 2.0 / M_PI >= s) {
		cout << "You can place square with area " << s << " into disk with area " << d << endl;
	}
	else {
		cout << "You cannot place square with area " << s << " into disk with area " << d << endl;
	}
	system("pause");
}