#include "student.h"
Student::Student(){}
std::istream& operator>>(std::istream& stream, Student& student){
    stream >> student.name >> student.group >> student.mark;
    return stream;
}
