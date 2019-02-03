#include <iostream>
#include <fstream>
#include <algorithm>
#include "coloureddetail.h"
#include "wheel.h"
#include "body.h"
using namespace std;
ofstream fout("output.txt");
struct colorGroup{
    int size;
    ColouredDetail ** group;
};
struct sizedColourGroups{
    colorGroup * collection;
    int size;
};
sizedColourGroups groupColors(ColouredDetail** details, int n){
    colorGroup* res = new colorGroup[1000];
    int counter = 0;
    res[counter].size = 1;
    res[counter].group = new ColouredDetail*[1000];
    res[counter].group[0] = details[0];
    for(int i = 1; i < n; i++){
        if(*(details[i]) == *(res[counter].group[0])){
            res[counter].group[res[counter].size] = details[i];
            res[counter].size++;
        } else {
            counter++;
            res[counter].size = 1;
            res[counter].group = new ColouredDetail*[1000];
            res[counter].group[0] = details[i];
        }
    }
    sizedColourGroups scg;
    scg.collection = res;
    scg.size = counter+1;
    return scg;
}
void printAllColors(ColouredDetail ** details, int n){
    cout << "All colors trucks" << endl;
    int bodies = 0;
    int wheels = 0;
    for(int j = 0; j < n; j++){
        if(dynamic_cast<Body*> (details[j]) != nullptr){
            bodies++;
        } else {
            wheels++;
        }
    }
    int allColorAmount = std::min(bodies, wheels / 4);
    cout << "------------------------------------------------------------" << endl;
    cout << "All colors: " << endl;
    cout << "Amount of multicoloured trucks: " << allColorAmount << endl;
    cout << "Remainder of this color: " << endl;
    cout << "Bodies: " << bodies - allColorAmount << endl;
    cout << "Wheels: " << wheels - allColorAmount * 4 << endl;
    cout << "------------------------------------------------------------" << endl;
    fout << "------------------------------------------------------------" << endl;
    fout << "All colors : "  << endl;
    fout << "Amount of multicoloured trucks: " << allColorAmount << endl;
    fout << "Remainder of this color: " << endl;
    fout << "Bodies: " << bodies - allColorAmount << endl;
    fout << "Wheels: " << wheels - allColorAmount * 4 << endl;
    fout << "------------------------------------------------------------" << endl;
}
void printMonocoloured(sizedColourGroups groups){
     cout << "Monocoloured trucks" << endl;
    for(int i = 0; i < groups.size; i++){
        int bodies = 0;
        int wheels = 0;
        for(int j = 0; j < groups.collection[i].size; j++){
            if(dynamic_cast<Body*> (groups.collection[i].group[j]) != nullptr){
                bodies++;
            } else {
                wheels++;
            }
        }
        int monoColouredtruckAmount = std::min(bodies, wheels / 4);
        cout << "------------------------------------------------------------" << endl;
        cout << "Color : " << groups.collection[i].group[0]->getColor() << endl;
        cout << "Amount of monocoloured trucks: " << monoColouredtruckAmount << endl;
        cout << "Remainder of this color: " << endl;
        cout << "Bodies: " << bodies - monoColouredtruckAmount << endl;
        cout << "Wheels: " << wheels - monoColouredtruckAmount * 4 << endl;
        cout << "------------------------------------------------------------" << endl;
        fout << "------------------------------------------------------------" << endl;
        fout << "Color : " << groups.collection[i].group[0]->getColor() << endl;
        fout << "Amount of monocoloured trucks: " << monoColouredtruckAmount << endl;
        fout << "Remainder of this color: " << endl;
        fout << "Bodies: " << bodies - monoColouredtruckAmount << endl;
        fout << "Wheels: " << wheels - monoColouredtruckAmount * 4 << endl;
        fout << "------------------------------------------------------------" << endl;
    }
}
void sortDetails(ColouredDetail** details, int n){
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if((*details[i]) >= (*details[j])){
                ColouredDetail * temp = details[i];
                details[i] = details[j];
                details[j] = temp;
            }
        }
    }
}
int main()
{
    int n;
    cout << "Enter number of details:" << endl;
    cin >> n;
    ColouredDetail** details = new ColouredDetail*[n];
    cout << "Enter details in next form:" << endl;
    cout << "[detail type] [color code]" << endl;
    cout << "Where [detail type] is W for wheel or B for body" << endl;
    cout << "[color code] - any positive integer number" << endl;
    char c;
    int color;
    for(int i = 0; i < n; i++){
        cin >> c >> color;
        switch(c){
            case 'w':
            case 'W':
                details[i] = new Wheel(color);
                break;
            case 'b':
            case 'B':
                details[i] = new Body(color);
                break;
        }
    }
    sortDetails(details, n);
    sizedColourGroups scg = groupColors(details, n);\
    printAllColors(details, n);
    printMonocoloured(scg);
    delete [] details;
    return 0;
}
