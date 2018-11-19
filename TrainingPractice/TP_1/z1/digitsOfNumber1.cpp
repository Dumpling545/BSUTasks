#include <iostream>
using namespace std;
/**
    Вариант 4

    Дано трехзначное число. В нем зачеркнули последнюю справа цифру и приписали ее в начале. Найти полученное число.

    Input       Ouput
    --------------------------------------------------------
    99          n should consist of three digits

    1000        n should consist of three digits

    -123        -312

    345         534

    120         12

*/
int main()
{
    int n;
    cout << "Enter n:" << endl;
    cin >> n;
    bool isMinus = false;
    if(n < 0){
        n*=-1;
        isMinus = true;
    }
    if(n < 100 || n > 999){
        cout << "n should consist of three digits" << endl;
    } else {
        int rightDigit = n % 10;
        n /= 10;
        n += 100 * rightDigit;
        if(isMinus){
            n*=-1;
        }
        cout << n;
    }
    system("pause");
    return 0;
}
