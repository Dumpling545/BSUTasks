#include "validator.h"
Validator::Validator(){}
bool Validator::validateFileName(const string filename){
    return !filename.empty() && filename.find(".") != string::npos;
}
bool Validator::validateInputStream(ifstream &fin){
    return fin.good() && fin.peek() != ifstream::traits_type::eof();
}
bool Validator::validateOrder(int order){
    return order == 0 || order == 1;
}


