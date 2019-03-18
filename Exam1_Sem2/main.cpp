#include <iostream>
#include <vector>
#include <iterator>
#include "filemanager.h"
#include "fisherman.h"
#include "fishermaninfo.h"
using namespace std;
enum AgeCategory{
    Under_18 = 0,
    From_18_to_30,
    Above_30
};
vector<FishermanInfo> convertToInfo(vector<Fisherman> fishermen){
    vector<FishermanInfo> fman_info;
    for_each(fishermen.begin(), fishermen.end(), [&fman_info](Fisherman f){
                 fman_info.push_back(FishermanInfo(f));
                 });
    return fman_info;
}
FishermanInfo *  leaderByWeight(vector<FishermanInfo> & fman_info, AgeCategory age_category){
    vector<FishermanInfo> selectedByAge;
    copy_if(fman_info.begin(), fman_info.end(), inserter(selectedByAge, selectedByAge.begin()),
            [age_category](FishermanInfo f){
                    return (bool)((AgeCategory::Under_18 == age_category)*(f.age < 18) +
                            (AgeCategory::From_18_to_30 == age_category)*(f.age >= 18 && f.age < 30) +
                            (AgeCategory::Above_30 == age_category) * (f.age >= 30));
                 });
    if(selectedByAge.size() != 0){
        vector<FishermanInfo>::iterator  it =  (std::max_element(selectedByAge.begin(), selectedByAge.end(),
                                                        [](FishermanInfo f1, FishermanInfo f2){
                                                            return f1.totalWeight < f2.totalWeight;
                                                        }));
        return new FishermanInfo(*it);
    } else {
        return nullptr;
    }
}
void printLeader(ostream &fout, FishermanInfo * leader, AgeCategory category){
    string categoryName;
    switch(category){
        case AgeCategory::Under_18:
            categoryName = "under-18";
            break;
        case AgeCategory::From_18_to_30:
            categoryName = "from-18-to-30";
            break;
        case AgeCategory::Above_30:
            categoryName = "above-30";
            break;
    }
    if(leader != nullptr){
        fout << "weight leader among "<<categoryName<< ": " << *leader << endl;
    } else {
        fout << "weight leader among "<<categoryName<< ": <no one participated in this age category>" << endl;
    }
}
void printInfoArray(ostream &fout, vector<FishermanInfo> fman_info, ostream_iterator<FishermanInfo> oo, string header){
    fout << endl<<header <<endl;
    copy(fman_info.begin() ,fman_info.end(),oo);
}
void sortByAge(vector<FishermanInfo>& fman_info){
    sort(fman_info.begin(), fman_info.end(),[](FishermanInfo f1, FishermanInfo f2){
                if(f1.age == f2.age){
                    if(f1.lastName == f2.lastName){
                        return f1.firstName < f2.firstName;
                    } else return f1.lastName < f2.lastName;
                } else return f1.age < f2.age;
             });
}
vector<FishermanInfo>  balanceByAge(vector<FishermanInfo> source){
    vector<FishermanInfo> res;
    for_each(source.begin(), source.end(), [&res](FishermanInfo f){
                 FishermanInfo f_copy = f;

                 if(f_copy.age <  18){
                    f_copy.totalWeight*=1.1;
                 } else if(f_copy.age >=  30){
                    f_copy.totalWeight*= 0.9;
                 }
                    res.push_back(f_copy);
    });
    return res;
}
int main()
{
    const int START = 2018;
    ifstream fin;
    ofstream fout;
    fout.open("output.txt");
    int year = START;
    fin.open("fishers" + std::to_string(year) +"_ANSI.txt");
    while(FileManager::checkInput(fin)){
        fout <<endl<< "                       YEAR " << year <<endl << endl;
        istream_iterator<Fisherman> ii{fin};
        istream_iterator<Fisherman> eos;
        vector<Fisherman> fishermen{ii, eos};
        vector<FishermanInfo> fman_info = convertToInfo(fishermen);
        printLeader(fout, leaderByWeight(fman_info, AgeCategory::Under_18), AgeCategory::Under_18);
        printLeader(fout, leaderByWeight(fman_info, AgeCategory::From_18_to_30), AgeCategory::From_18_to_30);
        printLeader(fout, leaderByWeight(fman_info, AgeCategory::Above_30), AgeCategory::Above_30);
        ostream_iterator<FishermanInfo> oo{fout,"\n"};
        printInfoArray(fout, fman_info, oo, "Name-weight-age list:");
        sortByAge(fman_info);
        printInfoArray(fout, fman_info, oo, "Sorted by age:");
        vector<FishermanInfo> fman_info_balanced = balanceByAge(fman_info);
        printInfoArray(fout, fman_info_balanced, oo, "Sorted and balanced by age:");
        fin.close();
        year--;
        fin.open("fishers" + std::to_string(year) +"_ANSI.txt");
    }
    return 0;
}
