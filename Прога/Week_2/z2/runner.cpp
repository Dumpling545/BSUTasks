#include <iostream>
/**
    � ������ ���� ��������� �������� x ����������, � ����� �� ������ ���� ���������� ������ �� 10% �� ����������� ��������.
    �� ������� ����� y ���������� ����� ���, �� ������� ������ ���������� �������� �� ����� y ����������.
    ��������, ��� ����� 10 20 ��������� ������ ������� 9. x � y � �������������� �����, ����� � ����� �����.

    ��������: �� ��������

    Input			Output
	--------------------------------------------------------------------------
	10 20           9 day(s)

	12.4 15.1       4 day(s)

	100 100         1 day(s)

	-10.9           x must be greater than zero. Re-enter x:

    10 -5           y must be greater than zero. Re-enter y:
*/
using namespace std;

int main()
{
    double x;
    double y;
    int day = 1;
    cout << "Enter x (km):" << endl;
    cin >> x;
    while(x < 0){
        cout << "x must be greater than zero. Re-enter x:" << endl;
        cin >> x;
    }
    cout << "Enter y (km):" << endl;
    cin >> y;
    while(y < 0){
        cout << "y must be greater than zero. Re-enter y:" << endl;
        cin >> y;
    }
    while(x < y){
        x*=1.1;
        day++;
    }
    cout << day <<" day(s)" <<endl;
    return 0;
}
