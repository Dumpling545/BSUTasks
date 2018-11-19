#include <fstream>
#include "queue.h"
#include "rational.h"

using namespace std;
/**
     ����� ���� ��� ������� X � Y, ���������� ����� �����.
     �� ������ ������� ������������ ����������� �� ������ ����� x � y ��������������.
     ���� x<y, �� ����� (x + y) ���������� � ����� ������� X, ����� ����� (x � y) ���������� � ����� ������� Y.
     ���������� ���������� ����� �����, ����� ������� ���� �� �������� ������ ������.
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
