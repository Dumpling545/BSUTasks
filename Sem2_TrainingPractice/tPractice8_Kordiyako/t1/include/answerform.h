#pragma once
#include<vector>
#include <cmath>
#include <iostream>
#include <windows.h>
//#include <windef.h>
#include "poll.h"
class AnswerForm
{
    public:
        AnswerForm(int amountOfQuestions);
        AnswerForm();
        UINT getCheckState(int question_id, int answer_id);
        void addAnswer(int question_id, int answer_id, bool value);
        double getResult(Poll poll);
    private:
        bool ** answers;
};
