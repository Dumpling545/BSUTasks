#include <iostream>
#include <list>
#include <algorithm>
using namespace std;
int main()
{
    std::list<int> iList;
    int n;
    cout << "Enter size:\n";
    cin >> n;
    iList.resize(n);
    cout << "\nEnter list:\n";
    std::generate(iList.begin(), iList.end(), [](){
        int element;
        cin >> element;
        return element;
    });
    /// output elements
    cout << "\nOutput list:\n";
    std::for_each(iList.begin(), iList.end(), [](int a){
        cout << a << ' ';
    });
    /// sort elements by absolute value
    iList.sort([](int a, int b)-> bool{
        return (std::abs(a) < std::abs(b));
    });
    cout << "\n\nSorted by absolute value list:\n";
    std::for_each(iList.begin(), iList.end(), [](int a){
        cout << a << ' ';
    });
    ///find first even number
    int found = *std::find_if(iList.begin(), iList.end(), [](int a){
        return (a % 2 == 0);
    });
    cout << "\n\nFirst even number: " << found <<'\n';
    ///count even numbers with for_each
    int sum = 0;
    std::for_each(iList.begin(), iList.end(), [&sum](int a){
        if(a % 2 == 0) sum += a;
    });
    cout << "\nSum of even numbers: " << sum <<'\n';
    ///replace negative numbers with zero
    std::replace_if(iList.begin(), iList.end(), [](int a){
        return (a < 0);
    }, 0);
    cout << "\nNegative replaced with zero:\n";
    std::for_each(iList.begin(), iList.end(), [](int a){
        cout << a << ' ';
    });
    return 0;
}
