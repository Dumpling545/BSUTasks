#pragma once
#include "question.h"
#include <vector>
class Poll
{
    public:
        Poll();
        std::string header;
        std::vector<Question> questions;
};
