#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "userCommands.h"
#include "mathException.h"
#include "nonExistCommandException.h"
#include "invalidCommandException.h"
#include "invalidOperationException.h"
#include "fileException.h"
#include "operationController.h"
#include "fileController.h"
#include "logger.h"
using namespace std;
class UserController{
    public:
        UserController();
        void executeCommand(string command);
    private:
        FileController * fileController;
        OperationController * operationController;
};
