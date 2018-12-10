#pragma once
#include <iostream>
#include <fstream>
#include <exception>
#include "trainService.h"
#include "train.h"
#include "validator.h"
using namespace std;
class UserController
{
private:
    TrainService * trainService;
    bool isload = false;
public:
    static const int LOAD = 0;
    static const int SORT_TIME = 1;
    static const int SORT_DEST = 2;
    static const int GET_AFTER = 3;
    static const int GET_DEST = 4;
    UserController();
    void handleCommand(int command);
    void printMenu();
    void startMenuInput();
};
