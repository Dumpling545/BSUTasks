#include <iostream>
#include "vector.h"
#include "vectorex.h"
using namespace std;

int main()
{
    Vector<double> vect(2, 0);
    Vectorex<double> vectEx(2, 0);
    vectEx.push_front(1);
    for(int i = 0; i < vectEx.getSize(); i++){
        cout << vectEx[i] <<endl;
    }
    return 0;
}
