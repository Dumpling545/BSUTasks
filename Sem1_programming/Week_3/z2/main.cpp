#include <iostream>

using namespace std;
/**
    Для заданного N найти все меньшие его автоморфные числа
    (автоморфным  называется  число,  совпадающее  с младшими цифрами своего квадрата).

    Input           Output
    ---------------------------------------------------------------

    0               no automorphic numbers

    -1              no automorphic numbers

    1               no automorphic numbers

    10000           1 5 6 25 76 376 625 9376

    -10000          -1 -5 -6 -25 -76 -376 -625 -9376

    1000000         1 5 6 25 76 376 625 9376 90625 109376 890625

*/
int main()
{
    int n;
    cout << "Enter n:" << endl;
    cin >> n;
    int sign = 1;
    while(n < 0){
        sign = -1;
        n*=-1;
    }

    if(n < 2){
        cout << "no automorphic numbers" << endl;
    }

    int degreeOfTen= 10;
    for(long long i = 1; i < n; i++){
        if(i / degreeOfTen == 1){
            degreeOfTen*=10;
        }
        if((i*i - i) % degreeOfTen == 0){
            cout << sign*i << " ";
        }
    }
    system("pause");
    return 0;
}
