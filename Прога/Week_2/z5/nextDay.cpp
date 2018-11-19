#include <iostream>

using namespace std;
/**
    Написать программу, которая вычисляет дату следующего дня.
    Например:
    Введите цифрами сегодняшнюю дату (число месяц год) –> 30 4 2016
    Вывести 01.05.2016

    Выполнил: Ян Кордияко

    Input			Output
	--------------------------------------------------------------------------
    1 4 2016        02.04.2016

    28 2 1959       01.03.1959

    31 12 1977      01.01.1778

    29 02 1600      01.03.1600

    29 02 1601      Incorrect day. Re-enter date:

    29 02 1604      01.03.1604

    29 02 1700      Incorrect day. Re-enter date:

    -2 3 1979       Incorrect day. Re-enter date:

    3 -2 1988       Incorrect month. Re-enter date:

    3 12 -4444      Incorrect year. Re-enter date:

    1 13 1978       Incorrect month. Re-enter date:

    32 2 1999       Incorrect day. Re-enter date:
*/
int main()
{
    //date
    //day
    int d;
    //month
    int m;
    //year
    int y;
    //number of months
    const int NUM_OF_MONTHS = 12;
    //amount of days in each month
    int months[NUM_OF_MONTHS] ={31,28,31,30,31,30,31,31,30,31,30,31};

    cout << "Enter date D M YYYY (or DD MM YYYY):" << endl;
    cin >> d >> m >> y;
    //check if year is leap
    if(y % 400 == 0 || (y % 100 != 0 && y % 4 == 0)){
        months[1] = 29;
    }
    while(y < 1){
        cout << "Incorrect year. Re-enter date:" << endl;
         cin >> d >> m >> y;
    }
    while(m<1 || m>12){
        cout << "Incorrect month. Re-enter date:" << endl;
        cin >> d >> m >> y;
    }
    while(d > months[m-1] || d < 1){
        cout << "Incorrect day. Re-enter date:" << endl;
        cin >> d >> m >> y;
    }
    d++;
    //next month
    if(d > months[m-1]){
        d = 1;
        m++;
    }
    //next year
    if(m > NUM_OF_MONTHS){
        m = 1;
        y++;
    }

    if(d < 10){
        cout<<"0";
    }
    cout<<d<<".";
    if(m < 10){
        cout<<"0";
    }
    cout<<m<<"."<<y;
    return 0;
}
