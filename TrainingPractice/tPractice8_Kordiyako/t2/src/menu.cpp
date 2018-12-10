#include "menu.h"

Menu::Menu(){}
void Menu::printHint(){
    cout << "COMMANDS:" << endl;
    cout <<"0 [filename] -  load sets from [filename]" <<endl;
    cout <<"                Note: sets in file should be divided by endline symbol for correct work" <<endl;
    cout <<"1 - Union(set#1, set#2)" <<endl;
    cout <<"2 - Intersection(set#1, set#2)" <<endl;
    cout <<"3 - Difference(set#1, set#2)" <<endl;
    cout <<"4 - Equality(set#1, set#2)" <<endl;
    cout <<"5 - Inclusion(set#1, set#2)" <<endl;
    cout <<"6 - Inclusion(set#2, set#1)" <<endl;
    cout <<"7 [set No.] [element] - set#[set No.].Add([element])" <<endl;
    cout <<"8 [set No.] [element] - set#[set No.].Remove([element])" <<endl;
    cout <<"                        Note: menu operates with only two sets (1,2)" <<endl;
    cout <<"9 [set No.] - print set#[set No.] in console" <<endl;
}

void Menu::startInput(){
    int command;
    while(cin >> command){
        handleCommand(command);
    }
}

void Menu::handleCommand(int command){
    switch(command){
        if(!isInit && command != Menu::LOAD){
            cout << "Load sets first" <<endl;
        } else {
            case Menu::LOAD:
                {
                    std::string filename;
                    cin >> filename;
                    std::ifstream fin;
                    fin.open(filename);
                    if(Validator::validateFileName(filename) && Validator::validateInputStream(fin)){
                        try{
                            fin >> s1;
                            fin >> s2;
                        }catch(...){
                            cout << "Invalid input" <<endl;
                            return;
                        }
                        fin.close();
                        isInit = true;
                    } else {
                        cout << "Invalid input" <<endl;
                    }
                }
                break;
            case Menu::UNION:
                {
                    cout << s1 + s2 << endl;
                }
                break;
            case Menu::INTERSECTION:
                {
                    cout << s1 * s2 << endl;
                }
                break;
            case Menu::DIFFERENCE:
                {
                    cout << (s1 - s2) << endl;
                }
                break;
            case Menu::EQUALITY:
                {
                    if(s1 == s2){
                        cout << "Set#1 and Set#2 are equal" << endl;
                    } else {
                        cout << "Set#1 and Set#2 are NOT equal" << endl;
                    }
                }
                break;
            case Menu::FIRST_INCLUDES_SECOND:
                {
                    if(s1 >= s2){
                        cout << "Set#1 includes Set#2" << endl;
                    } else {
                        cout << "Set#1 DOESN'T include Set#2" << endl;
                    }
                }
                break;
            case Menu::SECOND_INCLUDE_FIRST:
                {
                    if(s2 >= s1){
                        cout << "Set#2 includes Set#1" << endl;
                    } else {
                        cout << "Set#2 DOESN'T include Set#1" << endl;
                    }
                }
                break;
            case Menu::ADD:
                {
                    int setIndex;
                    char element;
                    cin >> setIndex;
                    if(Validator::validateSetIndex(setIndex)){
                        cin >> element;
                        switch(setIndex){
                            case 1:
                                s1.addElement(element);
                                break;
                            case 2:
                                s2.addElement(element);
                                break;
                        }
                    } else {
                        cout << "Only set#1 and set#2 are available for operations" <<endl;
                    }
                }
                break;
            case Menu::REMOVE:
                {
                    int setIndex;
                    char element;
                    cin >> setIndex;
                    if(Validator::validateSetIndex(setIndex)){
                        cin >> element;
                        switch(setIndex){
                            case 1:
                                s1.removeElement(element);
                                break;
                            case 2:
                                s2.removeElement(element);
                                break;
                        }
                    } else {
                        cout << "Only set#1 and set#2 are available for operations" <<endl;
                    }
                }
                break;
            case Menu::PRINT_SET:
                {
                    int setIndex;
                    cin >> setIndex;
                    if(Validator::validateSetIndex(setIndex)){
                        switch(setIndex){
                            case 1:
                                cout << s1 <<endl;
                                break;
                            case 2:
                                cout << s2 <<endl;
                                break;
                        }
                    } else {
                        cout << "Only set#1 and set#2 are available for operations" <<endl;
                    }
                }
                break;
        }
    }
}
