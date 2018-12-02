#include "fileController.h"
FileController::FileController(){

}
vector<string> FileController::read(string filename){
    try{
        openInputFile(filename);
        vector<string> result;
        string str;
        while(getline(fin,str)){
            result.push_back(str);
        }
        return result;
    } catch(FileException &ex){
        throw ex;
    }
}
void FileController::openInputFile(string filename){
    try{
        if(fin.is_open()){
            fin.close();
        }
        fin.open(filename);
    } catch(...){
        throw FileException(filename);
    }
    if(!fin){
        throw NonExistFileException(filename);
    } else if(fin.peek() == ifstream::traits_type::eof()){
        throw EmptyFileException(filename);
    }
}
void FileController::openOutputFile(string filename){
    try{
        if(fout.is_open()){
            fout.close();
        }
        fout.open(filename);
    } catch(...){
        throw FileException(filename);
    }
}
void FileController::write(string filename, string text){
    try{
        openOutputFile(filename);
        fout << text;
    } catch(FileException &ex){
        throw ex;
    }
}
