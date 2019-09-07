#include <iostream>

using namespace std;
/**
    Ќайти все натуральные числа, не превосход€щие заданного числа n, у которых все цифры в записи числа различны

     Input           Output
    ---------------------------------------------------------------
    -10             Incorrect input(n should be natural).Re-enter n:

    10              1 2 3 4 5 6 7 8 9 10

    100             1 2 3 4 5 6 7 8 9 10 12 13 14 15 16 17 18 19 20 21 23 24 25 26 27 28 29 30 31 32 34 35 36 37 38
                    39 40 41 42 43 45 46 47 48 49 50 51 52 53 54 56 57 58 59 60 61 62 63 64 65 67 68 69 70 71 72 73
                    74 75 76 78 79 80 81 82 83 84 85 86 87 89 90 91 92 93 94 95 96 97 98
*/
int main()
{
    int n;
    cout << "Enter n:" << endl;
    cin >> n;
    bool flags[10];
    bool isVariousDigits = true;
    for(int i = 0; i < 10; i++){
        flags[i] = false;
    }
    while(n < 1){
        cout << "Incorrect input(n should be natural).Re-enter n:" << endl;
        cin >> n;
    }
    for(int i = 1; i <= n; i++){
        int temp = i;
        isVariousDigits = true;
        while(temp > 0){
            if(flags[temp%10]){
                isVariousDigits = false;
                break;
            } else{
                flags[temp%10]=true;
                temp/=10;
            }
        }
        for(int j = 0; j < 10; j++){
            flags[j] = false;
        }
        if(isVariousDigits){
            cout << i << " ";
        }
    }
	system("pause");
    return 0;
}
