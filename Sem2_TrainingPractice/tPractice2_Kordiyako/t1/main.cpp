#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;
ifstream fin("input.txt");
int main()
{
    vector<int> vect;
    int elem;
    while(fin >> elem){
        vect.push_back(elem);
    }
    cout << "Max element: "<< *max_element(vect.begin(), vect.end()) << endl;
    cout << "Enter element: " << endl;
    cin >> elem;
    cout << "Amount of elements, equal to "<< elem << ": " << count(vect.begin(), vect.end(), elem) << endl;
    cout << "Amount of elements, bigger than 15:" << count_if(vect.begin(), vect.end(), [](int i){return i > 15;}) <<endl;
    cout << "Amount of numbers: " << vect.size() <<endl;
    cout << "Sum: " << accumulate(vect.begin(), vect.end(), 0) << endl;
    cout << "Average: " <<(double) accumulate(vect.begin(), vect.end(), 0) / vect.size() <<endl;
    return 0;
}
