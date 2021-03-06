#include "../include/practice2.h"
bool isCorrectInputFile(std::ifstream &_fin){
    bool res = true;
    if(!_fin){
        std::cout << "Input file doesn't exist" << std::endl;
        res =  false;
    } else if(_fin.peek() == std::ifstream::traits_type::eof()){
        std::cout << "Input file is empty" << std::endl;
        res = false;
    }
    return res;
}

int getMax(std::vector<int> &vect){
    return *std::max_element(vect.begin(), vect.end());
}

int getAmountOfElementsEqualTo(std::vector<int> &vect, int i){
    return std::count(vect.begin(), vect.end(), i);
}

int getAmountOfElementsBiggerThan(std::vector<int> &vect, int k){
    return count_if(vect.begin(), vect.end(), [k](int i){return i > k;});
}

int getAmountOfElements(std::vector<int> &vect){
    return vect.size();
}

int getSum(std::vector<int> &vect){
    return accumulate(vect.begin(), vect.end(), 0);
}

double getAverage(std::vector<int> &vect){
    return ((double) (accumulate(vect.begin(), vect.end(), 0) / vect.size()));
}


void getWordsStartWith(std::vector<std::string> &dest,
                       const std::vector<std::string> &src, char c){
    std::copy_if(src.begin(), src.end(), inserter(dest, dest.begin()),
                  [c] (std::string str){return str[0] == c;});
}
void deleteWordsStartWith(std::vector<std::string> &vect, char c){
    std::vector<std::string>::iterator p1=std::find_if(vect.begin(), vect.end(),
                                [c](const std::string & s) {return s[0] == c;});
    std::vector<std::string>::iterator p2=std::find_if(p1, vect.end(),
                                [c](const std::string & s) {return s[0] != c;});
    vect.erase(p1, p2);
}
void countWordRepeats(std::map<std::string, int> &dest,
                      const std::vector<std::string> &src){
    std::for_each(src.begin(), src.end(),
                  [&dest](std::string str){ dest[str]++;});
}

