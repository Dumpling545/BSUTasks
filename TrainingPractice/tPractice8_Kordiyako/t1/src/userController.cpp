#include "userController.h"

UserController::UserController()
{
}
void UserController::printMenu(){
    cout << "COMMANDS:" << endl;
    cout <<"0 [filename] - load  timetable from [filename]" <<endl;
    cout <<"1 [order] - get timetable sorted by departure time in ascending([order] = 0) or descending([order] = 1) order" <<endl;
    cout <<"2 [order] - get timetable sorted by destination in ascending([order] = 0) or descending([order] = 1) order" <<endl;
    cout <<"3 [hh:mm] - get all trains depart after [hh:mm]" <<endl;
    cout <<"4 [destination] - get all trains going to [destination]" <<endl;
    cout <<"Note that you're not allowed for commands 1 - 4 unless you load any timetable." <<endl;
    cout <<"Timetable's items should be in following format: [id] [destination] [departure time]" <<endl;
    cout <<"Example of item: 704A Hrodna 23:22" <<endl<<endl;
}
void UserController::startMenuInput(){
    cout << "Enter commands: " <<endl;
    int command;
    while(cin >> command){
        handleCommand(command);
    }
}
void UserController::handleCommand(int command){
    if(!isload && command != UserController::LOAD){
        cout << "You should load timetable first" <<endl;
    }else {
        switch(command){
            case UserController::LOAD:
                {
                    string filename;
                    cin >> filename;
                    ifstream fin;
                    fin.open(filename);
                    if(Validator::validateFileName(filename) && Validator::validateInputStream(fin)){
                        Train t;
                        vector<Train> trains;
                        while(!fin.eof()){
                            try{
                                fin >> t;
                            } catch(const char * s){
                                cout << s << " Item skipped." << endl;
                                continue;
                            }
                            trains.push_back(t);
                            cout << t <<endl;
                        }
                        fin.close();
                        trainService = new TrainService(trains);
                        vector<Train>().swap(trains);
                        isload = true;
                     }else {
                        cout << "Error while opening the file. Try again" <<endl;
                     }
                }
                break;
            case UserController::SORT_TIME:
                int order;
                cin >> order;
                if(Validator::validateOrder(order)){
                    vector<Train> query = trainService->sortByTime(order);
                    int length = query.size();
                    for(int i = 0; i < length; i++){
                        cout << query[i] <<endl;
                    }
                    vector<Train>().swap(query);
                } else {
                    cout << "Error: this parameter should be equal to 0 or 1" <<endl;
                }
                break;
            case UserController::SORT_DEST:
                int order2;
                cin >> order2;
                if(Validator::validateOrder(order2)){
                    vector<Train> query = trainService->sortByDestination(order2);
                    int length = query.size();
                    for(int i = 0; i < length; i++){
                        cout << query[i] <<endl;
                    }
                    vector<Train>().swap(query);
                } else {
                    cout << "Error: this parameter should be equal to 0 or 1" <<endl;
                }
                break;
            case UserController::GET_AFTER:
                {
                    string time;
                    cin >> time;
                    try{
                        vector<Train> query = trainService->getTrainsDepartsAfter(HMTime(time));
                        int length = query.size();
                        for(int i = 0; i < length; i++){
                            cout << query[i] <<endl;
                        }
                        if(length == 0){
                            cout << "No trains after " + time <<endl;
                        }
                        vector<Train>().swap(query);
                    } catch(const char * s){
                        cout << s <<endl;
                    }
                }
                break;
            case UserController::GET_DEST:
                {
                    string dest;
                    cin >> dest;
                    try{
                        vector<Train> query = trainService->getTrainsByDestination(dest);
                        int length = query.size();
                        for(int i = 0; i < length; i++){
                            cout << query[i] <<endl;
                        }
                        if(length == 0) {
                            cout << "No trains to " + dest <<endl;
                        }
                        vector<Train>().swap(query);
                    } catch(const char * s){
                        cout << s <<endl;
                    }
                }
                break;
            default:
                cout << "Error: Non-exist command. Try again" <<endl;
                break;
        }
    }
}
