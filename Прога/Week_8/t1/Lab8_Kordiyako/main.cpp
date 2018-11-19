#include <iostream>
#include "complexNumber.h"
#include "stack.h"
#include "queue.h"
using namespace std;
ComplexNumber maxComplex(ComplexNumber a, ComplexNumber b){
    if(a.abs() >= b.abs()){
        return a;
    } else {
        return b;
    }
}
ComplexNumber minComplex(ComplexNumber a, ComplexNumber b){
    if(a.abs() < b.abs()){
        return a;
    } else {
        return b;
    }
}
int main()
{
    int n = 0;
    double re = 0;
    double im = 0;
    cout << "Enter n: " << endl;
    cin >> n;
    while(n < 1){
        cout << "n>=1. Re-enter: " << endl;
        cin >> n;

    }
    ComplexNumber cNumbers[n];
    cout << "Enter complex numbers in the form '[real number] [imaginary number]': " << endl;
    Stack<ComplexNumber> st;
    Queue<ComplexNumber> qu;
    for(int i = 0; i < n; i++){
        cNumbers[i].get(cin);
        st.push(cNumbers[i]);
        qu.push(cNumbers[i]);
    }
    ComplexNumber minCN = cNumbers[0];
    ComplexNumber maxCN = cNumbers[0];
    for(int i = 1; i < n; i++){
        minCN = minComplex(minCN, cNumbers[i]);
        maxCN = maxComplex(maxCN, cNumbers[i]);
    }
    cout << "Max element: " << endl;
    maxCN.print(cout);
    cout <<endl << "Min element: " << endl;
    minCN.print(cout);
    cout << endl << "Stack: " << endl;
    while(!st.isEmpty()){
        st.pop().print(cout);
        cout <<endl;
    }
    cout << "Queue: " << endl;
    while(!qu.isEmpty()){
        qu.pop().print(cout);
        cout <<endl;
    }
    return 0;
}
