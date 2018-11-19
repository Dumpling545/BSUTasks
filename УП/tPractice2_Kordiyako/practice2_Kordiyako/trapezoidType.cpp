#include <iostream>
/**
    4.Известны углы α и β у основания трапеции.
    Выяснить, если это возможно, тип трапеции (прямоугольная, равнобедренная, прямоугольник).

    Input           Output
    -------------------------------------------------------------------
    0 0             Incorrect angles of trapezoid(0 < alpha, beta < 180).Please re-enter:

    1 180           Incorrect angles of trapezoid(0 < alpha, beta < 180).Please re-enter:

    45.45 45.45     This trapezoid is isosceles trapezoid

    90 15.7         This trapezoid is rectangular trapezoid

    16.8 90         This trapezoid is rectangular trapezoid

    90 90           This trapezoid is rectangle

    12 34           This trapezoid is just trapezoid
*/
using namespace std;

int main()
{
    const double RIGHT_ANGLE = 90;
    double alpha, beta;
    cout << "Enter angles (in degrees) at the base of trapezoid(alpha, beta): " <<endl;
    cin >> alpha >> beta;
    while(alpha <= 0 || alpha >= 180 || beta <= 0 || beta >= 180){
        cout << "Incorrect angles of trapezoid(0 < alpha, beta < 180).Please re-enter: "<< endl;
        cin >>alpha >> beta;
    }
    if(alpha == beta && alpha == RIGHT_ANGLE){
        cout << "This trapezoid is rectangle"<< endl;
    } else if(beta == alpha){
        cout << "This trapezoid is isosceles trapezoid"<< endl;
    } else if(beta == RIGHT_ANGLE || alpha == RIGHT_ANGLE){
        cout << "This trapezoid is rectangular trapezoid"<<endl;
    } else {
        cout << "This trapezoid is just trapezoid"<<endl;
    }
    system("pause");
    return 0;
}
