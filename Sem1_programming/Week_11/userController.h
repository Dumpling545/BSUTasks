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
#include "operationManager.h"
#include "fileManager.h"
#include "logger.h"
using namespace std;
class UserController{
    public:
        UserController();
        void executeCommand(string command);
    private:
        FileManager * fileManager;
        OperationManager * operationManager;
};
