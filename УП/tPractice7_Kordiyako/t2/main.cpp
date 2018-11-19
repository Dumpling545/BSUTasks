#include <iostream>
#include "vector.h"
using namespace std;

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
    v1+=v2;
    cout << v1[0] <<", " << v1[1] << ", " << v1[2] <<endl;
    return 0;
}
