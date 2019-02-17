#include <iostream>
#include "vector.h"
#include "charvectormanager.h"
/**
    Создайте vector<char>, содержащий буквы в алфавитном порядке.
    Распечатайте элементы этого вектора в прямом и обратном порядках.
*/
using namespace std;

int main()
{
    Vector<char> vect;
    for(char c = 'a'; c <= 'z'; c++){
        vect.push_back(c);
    }
    CharVectorManager manager(&vect);
    manager.print();
    manager.printReverse();
    return 0;
}
