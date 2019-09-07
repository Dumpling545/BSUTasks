#include <iostream>
#include <cmath>
using namespace std;
/** Вариант 4
    С начала суток часовая стрелка повернулась
    на у градусов (0 ≤ у < 360, y — вещественное число).
    Определить число полных часов и число полных минут,
    прошедших с начала суток.


    Input       Ouput
    --------------------------------------------------------
    -0.005      y must be not less than 0 and less than 360

    360         y must be not less than 0 and less than 360

    0.5         0h 1m

    30          1h 0m

    136.99      4h 33m

    237.49999   7h 54m

*/
int main()
{
    double y;

    cout << "Enter y:" << endl;
    cin >> y;
    if(y <0 || y >=360){
        cout << "y must be not less than 0 and less than 360" << endl;
    } else{
        /* For comfort, variable y is kept in int variable y2.
        In order not to lose accuracy in final result
        during type conversion (double -> int) it is multiplied by two
        (in this case, 1 minute will be represented by 1 degree instead of 0.5)
        */
        int y2 = 2 * y;
        const int HOUR_IN_DEGREES = 60;
        const int MINUTE_IN_DEGREES = 1;
        int minutes = floor((y2 % HOUR_IN_DEGREES) / MINUTE_IN_DEGREES);
        int hours = y2 / HOUR_IN_DEGREES;
        cout <<hours <<"h "<<minutes<<"m"<<endl;
    }
    system("pause");
    return 0;
}
