#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include "question.h"
#include "answer.h"
#include "poll.h"
class PollFactory
{
    public:
        static bool InitPoll(Poll &poll, std::string filename);
    private:
        PollFactory();
};

