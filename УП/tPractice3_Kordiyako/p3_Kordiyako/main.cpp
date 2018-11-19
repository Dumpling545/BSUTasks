#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include "getCPUTime.c"
#include "arrays.h"


using namespace std;
void testSorts(int * ar[4]){
    double startTime = 0;
    double endTime = 0;
    int *arraySelection[4];
    int *arrayInsertion[4];
    int *arrayBubble[4];
    int *arrayCoctail[4];
    int *arrayOddEven[4];
    int powTen = 10;
    for(int i = 0; i < 4; i++){

        arrayInsertion[i] = new int[powTen];
        arrayBubble[i] = new int[powTen];
        arrayCoctail[i] = new int[powTen];
        arrayOddEven[i] = new int[powTen];
        arraySelection[i] = new int[powTen];
        arraySelection[i] = ar[i];
        copyArray(arraySelection[i], arrayInsertion[i], powTen);
        copyArray(arraySelection[i], arrayBubble[i], powTen);
        copyArray(arraySelection[i], arrayCoctail[i], powTen);
        copyArray(arraySelection[i], arrayOddEven[i], powTen);
        powTen*=10;
    }
    cout<<setprecision(9) << endl;
    //selection
    powTen = 10;
    cout << "Selection sort |  ";
    for(int i = 0; i < 4; i++){
        startTime = getCPUTime();
        selectionSort(arraySelection[i], powTen);
        endTime = getCPUTime();
        cout << getCompares() << ", " << getSwaps() << ", " << endTime - startTime << ",    ";
        powTen*=10;
    }
    cout <<endl;

    //insertion
    powTen = 10;
    cout << "Insertion sort |  ";
    for(int i = 0; i < 4; i++){
        startTime = getCPUTime();
        insertionSort(arrayInsertion[i], powTen);
        endTime = getCPUTime();
        cout << getCompares() << ", " << getSwaps() << ", " << endTime - startTime << ",   ";
        powTen*=10;
    }
    cout <<endl;

    //bubble sort
    powTen = 10;
    cout << "Bubble sort    |  ";
    for(int i = 0; i < 4; i++){
        startTime = getCPUTime();
        bubbleSort(arrayBubble[i], powTen);
        endTime = getCPUTime();
        cout << getCompares() << ", " << getSwaps() << ", " << endTime - startTime << ",    ";
        powTen*=10;
    }
    cout <<endl;

    //coctail
    powTen = 10;
    cout << "Coctail sort   |  ";
    for(int i = 0; i < 4; i++){
        startTime = getCPUTime();
        coctailSort(arrayCoctail[i], powTen);
        endTime = getCPUTime();
        cout << getCompares() << ", " << getSwaps() << ", " << endTime - startTime << ",    ";
        powTen*=10;
    }
    cout << endl;

    //odd even
    powTen = 10;
    cout << "Odd-even sort  |  ";
    for(int i = 0; i < 4; i++){
        startTime = getCPUTime();
        oddEvenSort(arrayOddEven[i], powTen);
        endTime = getCPUTime();
        cout << getCompares() << ", " << getSwaps() << ", " << endTime - startTime << ",    ";
        powTen*=10;
    }
    cout << endl;
}
int main()
{
    cout << "RANDOM ARRAY: " << endl;
    cout << endl;
    cout << endl;
    int *ar[4];
    int powTen = 10;
    for(int i = 0; i <4; i++){
        ar[i] = new int[powTen];
        ar[i] = generateArray(powTen);
        powTen*=10;
    }
    testSorts(ar);
    cout << "...................................................................................................................." <<endl;
    cout << endl;
    cout << endl;
    cout << "RANDOM ARRAY: " << endl;
    cout << endl;
    cout << endl;
    powTen = 10;
    for(int i = 0; i <4; i++){
        ar[i] = new int[powTen];
        ar[i] = generateArray(powTen);
        powTen*=10;
    }
    testSorts(ar);
    cout << "...................................................................................................................." <<endl;
    cout << endl;
    cout << endl;
    cout << "RANDOM ARRAY: " << endl;
    cout << endl;
    cout << endl;
    powTen = 10;
    for(int i = 0; i <4; i++){
        ar[i] = new int[powTen];
        ar[i] = generateArray(powTen);
        powTen*=10;
    }
    testSorts(ar);
    cout << "...................................................................................................................." <<endl;
    cout << endl;
    cout << endl;
    cout << "SORTED (ASC) ARRAY:" << endl;
    cout << endl;
    cout << endl;
    powTen = 10;
    for(int i = 0; i <4; i++){
        ar[i] = new int[powTen];
        ar[i] = generateArray(powTen);
        selectionSort(ar[i], powTen);
        powTen*=10;
    }
    testSorts(ar);
    cout << "...................................................................................................................." <<endl;
    cout << endl;
    cout << endl;
    cout << "SORTED (DESC) ARRAY:" << endl;
    cout << endl;
    cout << endl;
    powTen = 10;
    for(int i = 0; i <4; i++){
        ar[i] = new int[powTen];
        ar[i] = generateArray(powTen);
        selectionSort(ar[i], powTen);
        reverseArray(ar[i], powTen);
        powTen*=10;
    }
    testSorts(ar);
	system("pause");
    return 0;
}
