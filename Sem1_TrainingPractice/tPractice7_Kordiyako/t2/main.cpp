#include <iostream>
#include "vector.h"
using namespace std;
/**��������� �������� ������ ��� ����������� ���������� �������� ����� ����� (��������).
������������� ����������� ��������� � ���������� �������� ������� � ��������� ������ �� ������� �������,
 ����������� ������� ������������ ������ �������� ��� �������� �������,
 ����������� ���������� �������� ������������� �������� � ��������� �������� � ����������� ��������� ��������,
 ��������� � ������� ���� ��������� ������� �� ������, ������ �� ����� �������� ������� �� ��������� �������,
 ������ �� ����� ����� �������. �������� ���������, ��������������� ������ � ���� �������.
��������� ������ ��������� ����, ����������� ����������� �������� ���� ������� ������.*/
void printVector(Vector<int> & v){
    cout << "(";
    int n =v.getSize();
    for(int i = 0; i< n; i++){
        cout<<v[i]<< ((i == (n-1)) ? ")" : ", ");
    }
    cout << endl;
}
void printElement(Vector<int> & v, int i){
    cout << v[i] << endl;
}
int main()
{
    Vector<int> v1(3);
    Vector<int> v2(3);
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v2.push_back(1);
    v2.push_back(0);
    v2.push_back(-1);
    v1 = v1 + v2;
    v1 -= v2*10;
    v1= v1* 4;
    v1/=2;
    printVector(v1);
    printVector(v2);
    return 0;
}
