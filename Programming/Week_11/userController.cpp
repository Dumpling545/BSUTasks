#include "userController.h"
UserController::UserController(){
    fileController = new FileController();
    operationController = new OperationController();
}
void UserController::executeCommand(string command){
    int c = command[0] - '0';
    string param = command.substr(1, command.size() - 1);
    switch(c){
        case UserCommands::CLOSE:
            exit(EXIT_SUCCESS);
            break;
        case UserCommands::OPEN_FILE:
            try{
                vector<string> data = fileController->read(param);
                operationController->createOperations(data);
            } catch(FileException &e){
                throw e;
            } catch(InvalidOperationException &e){
                cout << e.what() << endl;
            }
            break;
        case UserCommands::COMPUTE:
            try{
                operationController->runOperations();
            } catch(MathException &e){
                cout << e.what() << endl;
            }
            break;
        case UserCommands::WRITE_FILE:
            try{
                fileController->write(param, operationController->getResult());
            } catch(FileException &e){
                throw e;
            }
            break;
        default:
            throw NonExistCommandException();
            break;
    }
}
