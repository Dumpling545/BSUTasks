#include <iostream>
#include "week5.h"

using namespace std;
/**
     Написать программу, которая содержит функцию, принимающую в качестве аргумента,
     указатели на два массива (А и В) и размеры массивов. Функция проверяет,
     является ли массив В подмножеством/построкой (2 способами, см. зам.) массива А
     и возвращает указатель на начало найденного фрагмента, если элемента нет, возвращает 0.
    Зам. 1) Множество B называется подмножеством множества A, если все элементы, принадлежащие B, также принадлежат A.
            2) Подстрока – это непустая связная часть строки.


    Input                       Output
    ------------------------------------------------------------------
    -1                          Incorrect natural number. Re-enter:

    10                          Substring B located in array A at address(0 if nowhere): 0xc01774
    1 9 5 6 0 2 7 3 4 8         Set B is a subset of set A
    3
    2 7 3

    10                          Substring B located in array A at address(0 if nowhere): 0
    1 9 5 6 0 2 7 3 4 8         Set B is a subset of set A
    3
    2 3 7

    10                          Substring B located in array A at address(0 if nowhere): 0
    1 9 5 6 0 2 7 3 4 1         Set B is a subset of set A
    3
    1 9 9

    10                          Substring B located in array A at address(0 if nowhere): 0xb2176c
    7 8 9 -1 -1 2 9 4 5 0       Set B is a subset of set A
    3
    -1 -1 2
*/

int main()
{
    int n;
    enterNatural(n, "n");
    int *arrayA = new int[n];
    arrayA = enterArray(n, "A");

    int m;
    enterNatural(m, "m");
    int *arrayB = new int[m];
    arrayB = enterArray(m, "B");

    cout << "Substring B located in array A at address(0 if nowhere): " << isSubstring(arrayA, n, arrayB, m)<<endl;
    string res = isSubset(arrayA, n, arrayB, m)? "a" : "not a";
    cout << "Set B is " << res << " subset of set A" << endl;
    return 0;
}
