#include "log.h"
Log::Log(){}
Log::Log(string date, string message, string level){
    this->date = date;
    this->message = message;
    this->level = level;
}
