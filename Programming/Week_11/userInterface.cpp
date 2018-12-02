#include "userInterface.h"
UserInterface::UserInterface(){
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
void UserInterface::enterCommand(){
    string command;
    cin >> command;
    userController->executeCommand(command);
}
