#include <iostream>

using namespace std;
/**
    Дано натуральное число n. Определите, является ли оно степенью числа 2,
    и выведите слово YES, если является и слово NO, если не является.

    Выполнил: Ян Кордияко

	Input			Output
	--------------------------------------------------------------------------
	1024            YES
	3               NO
	-4              n is not natural .Re-enter n:
*/
int main()
{
    int n;
    int pow = 1;
    int base = 2;
    cout << "Enter n:" << endl;
    cin >> n;
    while(n < 1){
        cout << "n is not natural. Re-enter n:" << endl;
        cin >> n;
    }
    while(pow < n){
        pow *= base;
    }
    if(pow == n){
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
