#include <iostream>

using namespace std;
/**
    Вариант 4

    В трехзначном числе х зачеркнули первую цифру.
    Когда полученное число умножили на 10,
    а произведение сложили с первой цифрой числа х,
    то получилось число п. По заданному п найти число х

    (значение п вводится с клавиатуры, 1 < п < 999).

    Input       Ouput
    --------------------------------------------------------
    0           value of n should be in segment [1, 999]

    1000        value of n should be in segment [1, 999]

    -123        -312

    345         534

    120         12

    12          201

    9           900

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
    if(n < 1 || n > 999){
        cout << "value of n should be in segment [1, 999]" << endl;
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
