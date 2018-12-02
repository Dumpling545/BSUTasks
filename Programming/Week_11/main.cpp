#include <iostream>
#include <fstream>
#include <cstring>
#include <exception>
#include "rational.h"
using namespace std;
/**
    Доработать задание 1 из лабораторной работы 10 курса программирование (о рациональной дроби),
    добавив в приложение следующий функционал:

I)      Организовать меню пользователя для работы приложения (1- загрузить данные из файла,
        2 - вычислить результат, 3 - выгрузить результат в файл, 0 - выйти из приложения).

II)     Исходные данные для работы приложения загружать из файла, имя которого вводит пользователь
        (имя файла из каталога data в папке проекта или как полный путь к файлу – предусмотреть оба варианта).

III)    Имя выходного файла вводится пользователем.

IV)     Разработать собственные классы для обработки исключительных ситуаций.

V)      Разработать класс для хранения операций над двумя дробями (операция, операнд1, операнд 2). Разработать иерархию операций.

VI)     Разработать классы для валидации исходных данных.

VII)    Исходные данных хранить в виде списка операций.

VIII)   Данные в исходном файле представлены имеют следующую структуру:
        числитель/знаменатель операция числитель/знаменатель
        При этом, обязательным в дроби является только числитель (в этом случае знаменатель считается равным 1),
        и операция и вторая дробь могут отсутствовать.

IX)     В исходном файле не все строки могут быть корректными, это не должно приводить к аварийному завершению программы.
        Вычисления необходимо будет провести только для корректных данных (для строк, содержащих корректные данные).

X)      При работе приложения вести лог (записывать в файл log/log.txt), записывать информацию о том,
        когда и какой файл загружен или записан, номерах некорректных строк в исходном файле и т.д.
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
