#include "fileManager.h"
FileManager::FileManager(){

}
vector<string> FileManager::read(string filename){
    try{
        openInputFile(filename);
        vector<string> result;
        string str;
        while(getline(fin,str)){
            result.push_back(str);
        }
        fin.close();
        Logger::info("file '"+ filename +"' is read");
        return result;
    } catch(FileException &ex){
        Logger::warning(ex.what());
        throw;
    }
}
void FileManager::openInputFile(string filename){
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
void FileManager::openOutputFile(string filename){
    try{
        if(fout.is_open()){
            fout.close();
        }
        fout.open(filename);
    } catch(...){
        throw FileException(filename);
    }
}
void FileManager::write(string filename, string text){
    try{
        openOutputFile(filename);
        fout << text;
        fout.close();
        Logger::info("file '" + filename +  "' is written");
    } catch(FileException &ex){
        Logger::warning(ex.what());
        throw;
    }
}
