#include <iostream>
#include "set.h"
using namespace std;

int main()
{
    Set<int> set_int;
    Set<double> set_double;
    Set<string> set_string;
    //trying to add duplicate to set
    try{
        set_int.add(1);
        set_int.add(2);
        set_int.add(3);
        set_int.add(3);
    }catch(char const * message){
        cout << message << endl;
    }
    // trying to remove element from empty set
    try{
        set_double.remove(1.1);
    }catch(char const * message){
        cout << message << endl;
    }
    // trying to remove element which is not in the set
    try{
        set_string.add("abc");
        set_string.add("def");
        set_string.remove("ghi");
    }catch(char const * message){
        cout << message << endl;
    }
    Vector<int> setElems = set_int.get();
    int length = setElems.getSize();
    for(int i = 0; i < length; i++){
        cout << setElems[i] << endl;
    }
    return 0;
}
