#include <iostream>

using namespace std;
/**
    Найти количество различных цифр в записи заданного натурального числа.

    Input           Output
    ---------------------------------------------------------------
    0               n must be natural. Re-enter n:

    9               1

    1234567         7

    999999          1

    11223300        4

    123456789       9
*/
int main()
{
    bool flags[10];
    int result = 0;
    for(int i = 0; i < 10; i++){
        flags[i] = false;
    }
    int n = 0;
    cout << "Enter n:" << endl;
    cin >> n;
    while(n < 1){
        cout << "n must be natural. Re-enter n:" << endl;
        cin >> n;
    }
    while(n > 0){
        flags[n % 10] = true;
        n /= 10;
    }
    for(int i = 0; i < 10; i++){
        if(flags[i]){
            result++;
        }
    }
    cout << result << endl;
    system("pause");
    return 0;
}
