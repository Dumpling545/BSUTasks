#include <iostream>
#include <cmath>
#include "arrays.h"
#include "lab4.h"
using namespace std;
/**
    Найти сумму и произведение двух многочленов, заданных массивами своих коэффициентов


    Input                                   Output
    -------------------------------------------------------------------
    -1                                      Incorrect natural number. Re-enter:

    2 2                                     2 * x^2  -  4 * x^1  +  2
    1 -2 1                                  1 * x^4  -  4 * x^3  +  6 * x^2  -  4 * x^1  +  1
    1 -2 1

    2 1                                     1 * x^2  -  1 * x^1
    1 -2 1                                  1 * x^3  -  3 * x^2  +  3 * x^1  -  1
    -1 1

    3 3                                     5 * x^3  +  5 * x^2  +  5 * x^1  +  5
    1 2 3 4                                 4 * x^6  +  11 * x^5  +  20 * x^4  +  30 * x^3  +  20 * x^2  +  11 * x^1  +  4
    4 3 2 1

    2 2                                     1 * x^2  +  1
    1 0 0                                   1 * x^2
    0 0 1
*/

int main()
{
    int n,m;
    cout << "Enter degree of polynomial #1:" << endl;
    enterNatural(n);
    n++;
    cout << "Enter degree of polynomial #2:" << endl;
    enterNatural(m);
    m++;
    int maxNM = max(n, m);
    int * alphas = new int[maxNM];
    nullArray(alphas, maxNM);
    cout << "Polynomial coefficients #1:" <<endl;
    fillArray(alphas, n);
    reverseArray(alphas, maxNM);
    int * betas= new int[maxNM];
    nullArray(betas, maxNM);

    cout << "Polynomial coefficients #2:" <<endl;
    fillArray(betas, m);
    reverseArray(betas, maxNM);
    cout << "[#1 + #2]:" <<endl;
    printPolynomial(getSumPolynomial(alphas,betas,maxNM), maxNM);
    cout << "[#1 * #2]:" <<endl;
    printPolynomial(getMultiplicationPolynomial(alphas,betas,maxNM), 2*maxNM-1);
    system("pause");
    return 0;
}
