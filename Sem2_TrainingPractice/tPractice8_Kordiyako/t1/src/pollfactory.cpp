#include "pollfactory.h"
bool isCorrectInputFile(std::ifstream &_fin){
    bool res = true;
    if(!_fin){
        std::cout << "Input file doesn't exist" << std::endl;
        res =  false;
    } else if(_fin.peek() == std::ifstream::traits_type::eof()){
        std::cout << "Input file is empty" << std::endl;
        res = false;
    }
    return res;
}
void typifyQuestions(Poll &poll){
    int answerCounter = 0;
    for(int i = 0; i < poll.questions.size(); i++){
        for(int j = 0; j < poll.questions[i].answers.size(); j++){
            answerCounter+= ((int) poll.questions[i].answers[j].correct);
        }
        poll.questions[i].type = ((answerCounter == 1) ?
                                  QuestionType::OneAnswer :
                                      QuestionType::MultipleAnswer);
    }
}
bool verifyQuestions(Poll &poll){
    int answerCounter = 0;
    bool result = poll.questions.size() > 0;
    for(int i = 0; i < poll.questions.size() && result; i++){
        int ansNum = poll.questions[i].answers.size();
        if(ansNum < 2 || ansNum > 5){
            result = false;
            break;
        }
        for(int j = 0; j < poll.questions[i].answers.size(); j++){
            answerCounter+= ((int) poll.questions[i].answers[j].correct);
        }
        if(answerCounter == 0){
            result = false;
        }
    }
    return result;
}
void truncateString(std::string &str){
    str.erase(str.begin(),
                str.begin() + str.find_first_not_of(" \t\r\n"));
    str.erase(str.begin() + str.find_last_not_of(" \t\r\n") + 1,
               str.end());
}
void clearQuestion(Question & question){
    question.answers.clear();
    question.text = "";
    question.type = QuestionType::OneAnswer;
}
void clearAnswer(Answer &answer){
    answer = Answer("", false);
}
PollFactory::PollFactory()
{
    //ctor
}
void handleSymbol(std::ifstream &fin, char symbol, Poll &poll,
                  Question &question, Answer &answer, bool &fail){
    std::string temp;
    switch(symbol){
        case '<':{
            std::getline(fin, temp, '>');
            if(temp == "header"){
                std::getline(fin, temp, '<');
                truncateString(temp);
                poll.header = temp;
                std::getline(fin, temp, '>');
                fail = (temp != "/header");
            } else if(temp == "question"){
                clearQuestion(question);
            } else if(temp == "text"){
                std::getline(fin, temp, '<');
                truncateString(temp);
                question.text = temp;
                std::getline(fin, temp, '>');
                fail = (temp != "/text");
            } else if (temp == "answer"){
                clearAnswer(answer);
            } else if (temp == "statement"){
                std::getline(fin, temp, '<');
                truncateString(temp);
                answer.statement = temp;
                std::getline(fin, temp, '>');
                fail = (temp != "/statement");
            } else if(temp == "correct/"){
                answer.correct = true;
            } else if(temp == "/answer"){
                question.answers.push_back(answer);
            } else if(temp == "/question"){
                poll.questions.push_back(question);
            } else {
                fail = true;
            }
            break;
        }
        case ' ':
        case '\n':
            break;
        default:
            fail = true;
            break;
    }
}
bool PollFactory::InitPoll(Poll &poll, std::string filename){
    poll.questions.clear();
    bool fail = false;
    std::ifstream fin(filename);
    if(isCorrectInputFile(fin)){
        char symbol;
        Question question;
        Answer answer;
        while(fin >> symbol && !fail){
            handleSymbol(fin, symbol, poll, question,
                         answer, fail);
        }
        if(verifyQuestions(poll)) typifyQuestions(poll);
        else fail = true;
    } else {
        fail = true;
    }
    return !fail;
}
