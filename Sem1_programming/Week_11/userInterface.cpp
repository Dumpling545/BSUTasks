#include "userInterface.h"
UserInterface::UserInterface(){
    Logger::start();
    userController = new UserController();
}
void UserInterface::printMenu(){
    cout << "Commands :" <<endl;
    cout <<"1 [filename] -- open [filename] to read data for expression" <<endl;
    cout <<"2            -- compute expression" <<endl;
    cout <<"3 [filename] -- write result of computation into [filename]" << endl;
    cout <<"0            -- close program" << endl;
    cout << endl;
}
void UserInterface::commandConsole(){
    string command;
    while(getline(cin, command)){
        try{
            userController->executeCommand(command);
        } catch(FileException &ex){
            cout << "Invalid file: "<< ex.what() << endl;
            continue;
        } catch(InvalidCommandException &ex){
            cout << "Invalid command"<< endl;
            continue;
        }
    }
}
