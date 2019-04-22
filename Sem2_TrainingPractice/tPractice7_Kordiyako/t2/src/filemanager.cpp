#include "../include/filemanager.h"

bool FileManager::checkInput(std::ifstream & ifs){
    bool res = true;
    if(!ifs){
        res =  false;
    } else if(ifs.peek() == std::ifstream::traits_type::eof()){
        res = false;
    }
    return res;
}
