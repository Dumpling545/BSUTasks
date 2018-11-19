#include <iostream>
/**
    4. ƒано целое число в диапазоне 1 - 5.
    ¬ывести строку Ч словесное описание соответствующей оценки
    (1 Ч "плохо", 2 Ч "неудовлетворительно", 3 Ч "удовлетворительно", 4 Ч "хорошо", 5 Ч "отлично").

    Input           Output
    -------------------------------------------------------------------
    0               Incorrect mark(mark = 1,2,3,4,5).Please re-enter:

    6               Incorrect mark(mark = 1,2,3,4,5).Please re-enter:

    1               bad

    2               non-passing

    3               passing

    4               good

    5               excellent
*/
using namespace std;

int main()
{
    int n;
    cout << "Enter mark:" << endl;
    cin >> n;
    while (n < 1 || n > 5){
        cout << "Incorrect mark(mark = 1,2,3,4,5).Please re-enter:" << endl;
        cin >> n;
    }
    switch(n){
        case 5:
            cout << "excellent"<<endl;
            break;
        case 4:
            cout << "good" << endl;
            break;
        case 3:
            cout << "passing"<<endl;
            break;
        case 2:
            cout << "non-passing"<<endl;
            break;
        case 1:
            cout << "bad"<<endl;
            break;
    }
    system("pause");
    return 0;
}
