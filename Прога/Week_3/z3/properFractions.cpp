#include <iostream>

using namespace std;
/**
    Найти все несократимые дроби, знаменатель которых меньше заданного числа.

    Input           Output
    ---------------------------------------------------------------
    0               no fractions with absolute value of denominator less than 2

    -1              no fractions with absolute value of denominator less than 2

    1               no fractions with absolute value of denominator less than 2

    9               1/2  1/3  2/3  1/4  3/4  1/5  2/5  3/5  4/5
                    1/6  5/6  1/7  2/7  3/7  4/7  5/7  6/7  1/8
                    3/8  5/8  7/8

    10              1/2  1/3  2/3  1/4  3/4  1/5  2/5  3/5  4/5
                    1/6  5/6  1/7  2/7  3/7  4/7  5/7  6/7  1/8
                    3/8  5/8  7/8  1/9  2/9  4/9  5/9  7/9  8/9

    -10             -1/2  -1/3  -2/3  -1/4  -3/4  -1/5  -2/5
                    -3/5  -4/5  -1/6  -5/6  -1/7  -2/7  -3/7
                    -4/7  -5/7  -6/7  -1/8  -3/8  -5/8  -7/8
                    -1/9  -2/9  -4/9  -5/9  -7/9  -8/9
*/

//Euclid algorithm to find greatest common divider
int gcd(int a, int b){
    while(a != b){
        if(a > b){
            a-=b;
        } else {
            b-=a;
        }
    }
    return a;
}
int main()
{
    int n;
    //sign of input number
    int sign = 1;
    cout << "Enter n:" << endl;
    cin >> n;
    if(n < 0){
        sign=-1;
        n*=-1;
    }
    if(n < 2){
        cout << "no fractions with absolute value of denominator less than 2" << endl;
    } else {
        for(int i = 1; i < n; i++){
            for(int j = 1; j < i; j++){
                //check for coprime integers (by Euclide algorithm)
                if(gcd(i, j) == 1){
                    cout << sign*j << "/" << i << "  ";
                }
            }
        }
    }
    system("pause");
    return 0;
}
