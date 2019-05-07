#include "answer.h"
Answer::Answer()
{
    //ctor
}
Answer::Answer(std::string statement, bool correct){
    this->statement = statement;
    this->correct = correct;
}
