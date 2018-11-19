#include <iostream>

using namespace std;
/** Для заданного N найти все меньшие его совершенные числа
    (совершенным называется число, равное сумме всех своих
    делителей, не равных самому числу).

    Input           Output
    ---------------------------------------------------------------
    5               There are no perfect numbers, which absolute value is less than 6

    1000            6 28 496

    -1000           -6 -28 -496

    1000000         6 28 496 8128

*/
int main()
{
    int n;
    cout << "Enter n:" << endl;
    int sign = 1;
    cin >> n;
    if(n < 0){
        sign=-1;
        n*=-1;
    }
    for(long long i = 6; i < n; i++){
        long long res = 1;
        long long j = 2;
        while(j*j < i){
            if(i % j == 0){
                res += (j + i / j);
            }
            j++;
        }
        if(j*j == i){
            res+=j;
        }
        if(res == i){
            cout << sign*i << " ";
        }
    }
    if(n < 6){
        cout << "There are no perfect numbers, which absolute value is less than 6"<<endl;
    }
    system("pause");
    return 0;
}
