#include "hmtime.h"
string HMTime::get() const{
    string res = "";
    int hs = minutes/60;
    if(hs / 10 == 0){
        res="0";
    }
    res+=(to_string(hs) + ":");
    int ms = minutes % 60;
    if(ms / 10 == 0){
        res+="0";
    }
    res+=to_string(ms);
    return  res;
}
int HMTime::inMinutes() const{
    return minutes;
}
HMTime::HMTime(string str){
    int hours = 0;
    int minutes = 0;
    int * variable = &hours;
    bool findColon = false;
    int length = str.size();
    for(int i = 0; i < length; i++){
        char temp = str[i];
        if(isdigit(temp)){
            (*variable)*=10;
            (*variable)+=(temp-'0');
        }
        else if(!findColon && temp ==':'){
            findColon = true;
            variable = &minutes;
        }
        else{
            throw "Incorrect time!";
        }
    }
    if(!findColon){
        throw "Incorrect time!";
    }
    if(hours < 0 || hours > 23 || minutes < 0 || minutes > 59){
        throw "Incorrect time!";
    }
    else{
        this->minutes = hours * 60 + minutes;
    }
}
HMTime::HMTime(const HMTime& time){
    minutes = time.inMinutes();
}
HMTime::HMTime(){}
