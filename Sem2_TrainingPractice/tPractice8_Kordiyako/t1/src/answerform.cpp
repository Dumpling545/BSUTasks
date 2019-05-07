#include "answerform.h"

AnswerForm::AnswerForm()
{
    //ctor
}
AnswerForm::AnswerForm(int amountOfQuestions)
{
    answers = new bool*[amountOfQuestions];
    for(int i = 0; i < amountOfQuestions; i++){
        answers[i] = new bool[5];
        for(int j = 0; j < 5; j++){
            answers[i][j] = false;
        }
    }
}
UINT AnswerForm::getCheckState(int question_id, int answer_id){
    return ((answers[question_id][answer_id]) ? BST_CHECKED : BST_UNCHECKED);
}
void AnswerForm::addAnswer(int question_id, int answer_id, bool value){
    answers[question_id][answer_id] = value;
}
double AnswerForm::getResult(Poll poll){
    double result = 0;
    for(int i = 0; i < poll.questions.size(); i++){
        double temp = 1.0;
        double nullans = 1.0;
        for(int j = 0; j < poll.questions[i].answers.size(); j++){
            if(answers[i][j] != poll.questions[i].answers[j].correct){
                temp /= 2.0;
            }
            nullans /= 2.0;
        }
        bool isRadio = (poll.questions[i].type == QuestionType::OneAnswer);
        if(temp == nullans || isRadio) temp = floor(temp);
        result += temp;
    }
    return 100.0 * result / ((double) poll.questions.size());
}
