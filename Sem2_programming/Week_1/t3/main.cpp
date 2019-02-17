#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include<queue>
#include<stack>
#include<deque>
#include<list>
#include<vector>
/**
Создайте 3 различных контейнера, считайте в него числа из текстового файла. Выполните, не используя циклов:
    -	Подсчет количества чисел, равных заданному;
    -	Подсчет количества чисел, удовлетворяющих условию, например, «больше, чем 15»;
    -	Подсчет общего количества чисел;
    -	Подсчет суммы чисел;
    -	Подсчет среднего арифметического чисел.
*/
using namespace std;
ifstream fin("input.txt");

int main()
{
    stack<double> _stack;
    queue<double> _queue;
    deque<double> _deque;
    list<double> _list;
    vector<double> _vector;
    double d;
    while(fin >> d){
        _stack.push(d);
        _queue.push(d);
        _deque.push_back(d);
        _list.push_back(d);
        _vector.push_back(d);
    }
    // counting numbers equal to 1.1
    double eqNumber = 1.1;
    int resultEqual = count(_deque.begin(), _deque.end(), eqNumber);
    cout << "Numbers equal to " << eqNumber <<": "<<   resultEqual << endl;
    // counting number bigger than 15
    double biggerThan = 15.0;
    int resultBiggerThan = count_if(_list.begin(), _list.end(), [biggerThan](double & d) {return d > biggerThan;});
    cout << "Numbers bigger than " << biggerThan << ": " << resultBiggerThan << endl;
    // counting all numbers
    int resultAllNumbers = count_if(_vector.begin(), _vector.end(), [](double & d) {return true;});
    cout << "All numbers: " << resultAllNumbers << endl;
    // counting sum
    double resultSum = accumulate(_deque.begin(), _deque.end(), 0.0, [](const double& x, const double& y) {return x + y;});
    cout << "Sum: " <<setprecision(8)<< resultSum << endl;
    //counting average
    double resultAverage = resultSum / ((double)resultAllNumbers);
    cout << "Average: "<<setprecision(8)<< resultAverage << endl;
    return 0;
}
