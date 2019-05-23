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
        std::cout << "Max element: " << getMax(vect) <<'\n';

        int elem;
        enterElement<int>(elem);

        std::cout << "Amount of elements, equal to "<< elem << ": ";
        std::cout << getAmountOfElementsEqualTo(vect, elem) <<'\n';

        std::cout << "Amount of elements, bigger than "<< elem <<": ";
        std::cout << getAmountOfElementsBiggerThan(vect, elem) <<'\n';

        std::cout << "Amount of numbers: ";
        std::cout << getAmountOfElements(vect) << '\n';

        std::cout << "Sum: ";
        std::cout << getSum(vect) <<'\n';

        std::cout << "Average: ";
        std::cout << getAverage(vect) << '\n';
    }
    return 0;
}
