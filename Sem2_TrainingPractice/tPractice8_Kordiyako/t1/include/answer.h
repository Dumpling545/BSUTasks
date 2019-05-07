#pragma once
#include <string>
class Answer
{
    public:
        Answer();
        Answer(std::string statement, bool correct);
        std::string statement;
        bool correct;
};
