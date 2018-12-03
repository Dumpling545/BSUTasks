#pragma once
#include<iostream>
#include "nonExistCommandException.h"
#include "fileException.h"
#include "userController.h"
#include "logger.h"
class UserInterface{
    public:
        UserInterface();
        void printMenu();
        void commandConsole();
    private:
        UserController * userController;
};
