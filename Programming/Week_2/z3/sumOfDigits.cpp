#include <iostream>

using namespace std;
/**
    Дано натуральное число n. Выведите сумму цифр числа n.

    Выполнил: Ян Кордияко

    Input			Output
	--------------------------------------------------------------------------
	-10             n must be natural. Re-enter n:

	123456          21

	1000000         1

*/
int main()
{
    int n;
    int result = 0;
    cout << "Enter n: " <<endl;
    cin >> n;
    while(n < 1){
        cout << "n must be natural. Re-enter n: " <<endl;
        cin >> n;
    }
    while(n > 0){
        result += n % 10;
        n /= 10;
    }
    cout << result<< endl;
    return 0;
}
