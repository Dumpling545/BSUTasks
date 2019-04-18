#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <numeric>
#include "include/practice2.h"
using namespace std;
ifstream fin("input.txt");
int main()
{
    if(isCorrectInputFile(fin)){
        vector<int> vect;
        fillVector(fin, vect);
        printMax(vect);
        int elem;
        enterInteger(elem);
        printAmountOfElementsEqualTo(vect, elem);
        printAmountOfElementsBiggerThan(vect, 15);
        printAmountOfElements(vect);
        printSum(vect);
        printAverage(vect);
    }
    return 0;
}
