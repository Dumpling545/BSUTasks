#include <iostream>

using namespace std;
/** Найти k-ую цифру в ряду цифр, составленных из подряд идущих натуральных чисел, начиная с 1: 12345678910111213…

    Input           Output
    ---------------------------------------------------------------
    -5              Incorrect number(k should be natural. Re-enter k:

    1               1

    9               9

    10              1

    189             9

    190             1
*/
int getDigit(int k){
    int digitsByNumber = 1;
    int powerOfTen = 1;
    int number = 0;
    while(k > 9 * powerOfTen * digitsByNumber){
        k -= 9*powerOfTen * digitsByNumber;
        number += 9*powerOfTen;
        digitsByNumber++;
        powerOfTen*=10;
    }
    number += k/digitsByNumber;
    int position = k % digitsByNumber;
    if(position == 0){
        return number % 10;
    } else {
        number++;
        position = digitsByNumber - position;
        for(int i = 0; i < position; i++){
            number /= 10;
        }
        return number % 10;
    }
}
int main()
{
    int k;
    cout << "Enter k:" << endl;
    cin >> k;
    while(k < 1){
        cout << "Incorrect number(k should be natural. Re-enter k: " << endl;
        cin >> k;
    }
    cout << getDigit(k);
    system("pause");
    return 0;
}
