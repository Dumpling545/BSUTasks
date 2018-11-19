#include <iostream>
/**
    4. Даны координаты двух различных полей шахматной доски x1, y1, x2, y2 (целые числа, лежащие в диапазоне 1–8).
    Проверить истинность высказывания: «Король за один ход может перейти с одного поля на другое».

    Input           Output
    -------------------------------------------------------------------
    0 0             Incorrect coordinates (must be between 1 and 8). Please re-enter:

    1 1             Incorrect coordinates (must be between 1 and 8). Please re-enter:
    2 9

    1 1             Incorrect coordinates ( (x1,y1) can't be equal to (x2,y2) ). Please re-enter:
    1 1

    1 1             You can move king to 2 1 from 1 1
    2 1

    1 1             You can move king to 1 2 from 1 1
    1 2

    1 1             You can move king to 2 2 from 1 1
    2 2

    1 1             You CANNOT move king to 1 3 from 1 1
    1 3

    1 1             You CANNOT move king to 3 1 from 1 1
    3 1


*/
using namespace std;

int main()
{
    int x1,y1;
    int x2,y2;
    cout << "Enter (x1;y1) - current coordinates of king: " << endl;
    cin >> x1 >> y1;
    while(x1 < 1 || x1 > 8 || y1 < 1 || y1 > 8){
        cout << "Incorrect coordinates (must be between 1 and 8). Please re-enter:" << endl;
        cin >>x1 >>y1;
    }
    cout << "Enter (x2;y2) - move of king you want to make: " << endl;
    cin >>x2 >> y2;
    while(x2 < 1 || x2 > 8 || y2 < 1 || y2 > 8){
        cout << "Incorrect coordinates (must be between 1 and 8). Please re-enter:" << endl;
        cin >>x2 >> y2;
    }
    while(x2==x1 && y2==y1){
        cout << "Incorrect coordinates ( (x1,y1) can't be equal to (x2,y2) ). Please re-enter:" << endl;
        cin >>x2 >> y2;
    }
    /** In order to omit a lot of if-else-conditions, sum of squared deltas (s.s.d) of X and Y coordinates
        will be used. King is moved to any of 8 surrounding cells. It means that s.s.d. can take next values:
        a) 1 = 1^2 + 0^2 = 0^2 + 1^2 - if king is moved to right, left, forward back
        b) 2 = 1^2 + 1^2 - in other cases
        If king can't be moved due to coordinates, s.s.d. will take a value of 4 and greater:
        4 <= 2^2 + N^2, where N = 0, 1, 2...
    */
    int deltaXSquared = (x2-x1)*(x2-x1);
    int deltaYSquared = (y2-y1)*(y2-y1);
    int sumDeltaSquared = deltaXSquared + deltaYSquared;
    if(sumDeltaSquared <= 2){
        cout << "You can move king to "<<x2<<" " <<y2<<" from "<<x1 <<" "<<y1<<endl;
    } else {
        cout << "You CANNOT move king to "<<x2<<" " <<y2<<" from "<<x1 <<" "<<y1<<endl;
    }
    system("pause");
    return 0;
}
