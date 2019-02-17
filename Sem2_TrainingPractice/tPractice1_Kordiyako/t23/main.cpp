#include <iostream>
#include <stack>
#include "sll_vector.h"
#include "sll_iterator.h"
using namespace std;

/**
    –азработать класс Ђќдномерный целочисленный массивї на базе линейного односв€зного списка.
    ѕо своим возможност€м класс должен поддерживать реализацию основных методов стандартного класса vector и,
    дополнительно, обеспечивать добавление нового элемента в начало вектора.
    ƒобавить в класс возможность работы с итераторами.
    ѕродемонстрировать возможности разработанного класса.
*/
void print(SLL_vector<int> vect){
    cout << endl << "   vector: | ";
    SLL_iterator<int> iterator = vect.begin();
    while(iterator != vect.end()){
        cout << iterator.get() << " | ";
        iterator++;
    }
    cout << endl << "   size: " << vect.size() <<endl <<endl;
}
int main()
{
    SLL_vector<int> vect;
    cout << "Action: push_back, params: <1, 2>:" <<endl;
    vect.push_back(1);
    vect.push_back(2);
    print(vect);
    cout << "Action: push_front, params: <-1, 0>:" <<endl;
    vect.push_front(-1);
    vect.push_front(0);
    print(vect);
    cout << "Action: insert, params: <{2, 10}, {1, 100}>:" <<endl;
    vect.insert(2, 10);
    vect.insert(1, 100);
    print(vect);
    cout << "Action: pop_front:" << endl;
    vect.pop_front();
    print(vect);
    cout << "Action: pop_back:" << endl;
    vect.pop_back();
    print(vect);
    cout << "Action: erase, params: <1>:" <<endl;
    vect.erase(1);
    print(vect);
    cout << "Action: [], params: <1>:" << endl;
    cout << vect[1] <<endl;
    return 0;
}
