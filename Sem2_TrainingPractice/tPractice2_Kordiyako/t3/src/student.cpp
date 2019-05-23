#include "student.h"
Student::Student(){}
std::istream& operator>>(std::istream& stream, Student& student){
    stream >> student.name >> student.group >> student.mark;
    return stream;
}
std::ostream& operator<<(std::ostream& stream, const Student& student){
    stream << std::setw(20) << student.name
    << std::setw(5)<< student.group <<std::setw(5)<<student.mark<<'\n';
    return stream;
}
