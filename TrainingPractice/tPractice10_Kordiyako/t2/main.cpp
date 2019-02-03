#include <iostream>
#include "vector.h"
using namespace std;

int main()
{
    //default constructor
    Vector<int> vect1;
    //constructor with size and fill-value
    Vector<int> vect2(20, 0);
    //copy constructor
    Vector<int> vect3(vect2);
    //0 should be printed due to second constructor
    cout << vect2[7] << endl;
    vect2[7] = 5;
    //after changing value of element in vect2 using operator[] 5 should be printed
    cout << vect2[7] << endl;
    // 20 should be printed due to 3rd constructor
    cout << vect3.getSize() << endl;
    vect3.push_at(5, 10000);
    // 21 and 10000 should be printed after pushing new element in vect3
    cout << vect3.getSize() <<" " << vect3[5] << endl;
    vect3.pop_back();
    // 20 should be printed after deleting last element in vect3
    cout << vect3.getSize() << endl;
    return 0;
}
