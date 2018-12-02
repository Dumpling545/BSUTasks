#pragma once
#include<iostream>
#include "userController.h"
#include "logger.h"
class UserInterface{
    public:
        UserInterface();
        void printMenu();
        void enterCommand();
    private:
        UserController * userController;
};
