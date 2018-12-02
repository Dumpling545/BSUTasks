#include <iostream>
#include <fstream>
#include <cstring>
#include <exception>
#include "rational.h"
using namespace std;
/**
    ���������� ������� 1 �� ������������ ������ 10 ����� ���������������� (� ������������ �����),
    ������� � ���������� ��������� ����������:

I)      ������������ ���� ������������ ��� ������ ���������� (1- ��������� ������ �� �����,
        2 - ��������� ���������, 3 - ��������� ��������� � ����, 0 - ����� �� ����������).

II)     �������� ������ ��� ������ ���������� ��������� �� �����, ��� �������� ������ ������������
        (��� ����� �� �������� data � ����� ������� ��� ��� ������ ���� � ����� � ������������� ��� ��������).

III)    ��� ��������� ����� �������� �������������.

IV)     ����������� ����������� ������ ��� ��������� �������������� ��������.

V)      ����������� ����� ��� �������� �������� ��� ����� ������� (��������, �������1, ������� 2). ����������� �������� ��������.

VI)     ����������� ������ ��� ��������� �������� ������.

VII)    �������� ������ ������� � ���� ������ ��������.

VIII)   ������ � �������� ����� ������������ ����� ��������� ���������:
        ���������/����������� �������� ���������/�����������
        ��� ����, ������������ � ����� �������� ������ ��������� (� ���� ������ ����������� ��������� ������ 1),
        � �������� � ������ ����� ����� �������������.

IX)     � �������� ����� �� ��� ������ ����� ���� �����������, ��� �� ������ ��������� � ���������� ���������� ���������.
        ���������� ���������� ����� �������� ������ ��� ���������� ������ (��� �����, ���������� ���������� ������).

X)      ��� ������ ���������� ����� ��� (���������� � ���� log/log.txt), ���������� ���������� � ���,
        ����� � ����� ���� �������� ��� �������, ������� ������������ ����� � �������� ����� � �.�.
*/
ifstream fin;
ofstream fout;
void openOutputFile(ofstream &_fout, char * fileName){
    try{
        if(_fout.is_open()){
            _fout.close();
        }
        _fout.open(fileName);
    } catch(int k){
        throw "Exception while opening the file";
    }
}
void openInputFile(ifstream &_fin, char * fileName){
    try{
        if(_fin.is_open()){
            _fin.close();
        }
        _fin.open(fileName);
    } catch(int k){
        throw "Exception while opening the file";
    }
    if(!(_fin &&  _fin.peek() != ifstream::traits_type::eof())){
        throw "Input file doesn't exist or empty";
    }
}
enum codes {
    download = 1,
     compute,
     upload,
     close = 0
};
int main()
{
    cout << "Commands :" <<endl;
    cout <<"1 [filename] -- open [filename] to read data for expression" <<endl;
    cout <<"2            -- compute expression" <<endl;
    cout <<"3 [filename] -- write result of computation into [filename]" << endl;
    cout <<"0            -- close program" << endl;
    cout << endl;
    char * inputFile = new char[100];
    char * outputFile = new char[100];
    int i = 0;


    bool stop = false;
    while(!stop && cin >> i){
        try{
            switch(i){
                case download:
                    cin >> inputFile;
                    openInputFile(fin, inputFile);
                    break;
                case compute:

                    break;
                case upload:
                    cin >> outputFile;
                    openOutputFile(fout, outputFile);
                    //TODO: fout << result;
                    break;
                case close:
                    stop = true;
                    break;
            }
        } catch(const char* s){
            stop = true;
            cout << "Exception: " <<  s << endl;
        }
    }
    /*Rational r1(-3003,2210);
    Rational r2(-1,-3);
    r1.print(cout);
    cout << " + ";
    r2.print(cout);
    cout << " = ";
    (r1 + r2).print(cout);
    cout << endl;
    r1.print(cout);
    cout << " - ";
    r2.print(cout);
    cout << " = ";
    (r1 - r2).print(cout);
    cout << endl;
    r1.print(cout);
    cout << " * ";
    r2.print(cout);
    cout << " = ";
    (r1 * r2).print(cout);
    cout << endl;
    r1.print(cout);
    cout << " / ";
    r2.print(cout);
    cout << " = ";
    (r1 / r2).print(cout);
    cout << endl;
    if(r1 > r2){
        r1.print(cout);
        cout << " > ";
        r2.print(cout);
    } else if(r1 < r2){
        r1.print(cout);
        cout << " < ";
        r2.print(cout);
    } else {
        r1.print(cout);
        cout << " == ";
        r2.print(cout);
    }*/
    cout << "Prorgam closed" <<endl;
    return 0;
}
