#include <fstream>
#include "queue.h"
#include "rational.h"

using namespace std;
/**
     Пусть даны две очереди X и Y, содержащие целые числа.
     Из каждой очереди одновременно извлекается по одному числу x и y соответственно.
     Если x<y, то число (x + y) помещается в конец очереди X, иначе число (x – y) помещается в конец очереди Y.
     Необходимо определить число шагов, через которые одна из очередей станет пустой.
*/
ofstream fout("output.txt");
ifstream fin("input.txt");
bool isCorrectInputFile(ifstream &_fin){
    if(_fin &&  _fin.peek() != ifstream::traits_type::eof()){
        return true;
    } else {
        cout << "Input file doesn't exist or empty" << endl;
        return false;
    }
}
int main()
{
    Queue<int> x;
    Queue<int> y;
    if(isCorrectInputFile(fin)){
        int m;
        int input;
        fin >> m;
        for(int i = 0; i < m; i++){
            fin >> input;
            x.push(input);
        }
        fin >> m;
        for(int i = 0; i < m; i++){
            fin >> input;
            y.push(input);
        }
    }
    int i = 0;
    while(!x.isEmpty() && !y.isEmpty()){
        if(x.first() < y.first()){
            x.push(x.pop() + y.pop());
        } else {
            y.push(x.pop() - y.pop());
        }
        ++i;
    }
    fout << i << endl;
    return 0;
}
