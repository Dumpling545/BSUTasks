#include <iostream>
#include <cmath>
#include<climits>
#include<iomanip>
extern "C" float __fastcall  compute_ln_2(int);
extern "C" float __fastcall  const_ln_2();
void main()
{
	float precision;
	std::cout << "Enter precision:\n";
	std::cin >> precision;
	float delta = 10;
	//float cln_2 = const_ln_2();
	int i;
	float f_prev = 0, f_next;
	for (i = 1; i < INT_MAX && delta > precision; i++) {
		f_next = compute_ln_2(i);
		delta = fabs(f_next - f_prev);
		f_prev = f_next;
	}
	std::cout << "k is bigger than or equal to " <<--i <<'\n';
	std::cout << "for k = " << i <<" we get " <<std::setprecision(12) << f_next << '\n';
	system("pause");
}
