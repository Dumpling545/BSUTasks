#include "header.h"
bool isCorrectInputFile(ifstream &_fin){
    if(_fin &&  _fin.peek() != ifstream::traits_type::eof()){
        return true;
    } else {
        cout << "Input file doesn't exist or empty" << endl;
        return false;
    }
}
