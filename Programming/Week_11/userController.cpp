#include "userController.h"
UserController::UserController(){
    fileController = new FileController();
    operationController = new OperationController();
}
void UserController::executeCommand(string command){
    int c = command[0] - '0';
    string param;
    if(command.size() > 1){
        if(command[1] != ' '){
            throw InvalidCommandException();
        }
        param = command.substr(2, command.size() - 2);
    }
    switch(c){
        case UserCommands::CLOSE:
            Logger::info("Command sent: " + to_string(c));
            exit(EXIT_SUCCESS);
            break;
        case UserCommands::OPEN_FILE:
            try{
                Logger::info("Command sent: " + to_string(c));
                vector<string> data = fileController->read(param);
                operationController->createOperations(data);
            } catch(FileException &e){
                throw;
            } catch(InvalidOperationException &e){
                cout << e.what() << endl;
            }
            break;
        case UserCommands::COMPUTE:
            try{
                Logger::info("Command sent: " + to_string(c));
                operationController->runOperations();
            } catch(MathException &e){
                cout << e.what() << endl;
            }
            break;
        case UserCommands::WRITE_FILE:
            try{
                Logger::info("Command sent: " + to_string(c));
                fileController->write(param, operationController->getResult());
            } catch(FileException &e){
                throw;
            }
            break;
        default:
            Logger::warning("Command doesn't exist: " + to_string(c));
            throw NonExistCommandException();
            break;
    }
}
