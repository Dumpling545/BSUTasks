#include "student.h"
std::ostream& operator<<(std::ostream &stream, const Student& student){
    stream << student.name << ' ' << student.group << "  ";
    for(int i = 0; i < student.examsResult.size(); i++){
        stream << student.examsResult[i] << " ";
    }
    return stream;
}

std::istream& operator>>(std::istream& stream, Student& student){
    stream >> student.name >> student.group;
    int temp;
    while(stream >> temp){
        student.examsResult.push_back(temp);
    }
    return stream;
}
