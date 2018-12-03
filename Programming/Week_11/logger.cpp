#include "logger.h"
void Logger::info(string message){
    time_t now = time(0);
    string  date(ctime(&now));
    Log log(date, message, "INFO");
    save(log);
}
void Logger::warning(string message){
    time_t now = time(0);
    string  date(ctime(&now));
    Log log(date, message, "WARNING");
    save(log);
}
void Logger::save(Log log){
    string logString = log.date + ": [" + log.level + "] " + log.message;
    try{
        ofstream fout("log/log.txt", std::ios::app);
        fout << logString << endl;
        fout.close();
    }catch(...){}
}
void Logger::start(){
    try{
        ofstream fout("log/log.txt");
        fout << "";
        fout.close();
    }catch(...){}
}
