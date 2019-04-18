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
void printMax(std::vector<int> &vect){
    std::cout << "Max element: ";
    std::cout << *std::max_element(vect.begin(), vect.end());
    std::cout << '\n';
}
void enterInteger(int &i){
    std::cout << "Enter element: " << '\n';
    std::cin >> i;
}
void printAmountOfElementsEqualTo(std::vector<int> &vect, int i){
    std::cout << "Amount of elements, equal to "<< i << ": ";
    std::cout << std::count(vect.begin(), vect.end(), i);
    std::cout << '\n';
}
void printAmountOfElementsBiggerThan(std::vector<int> &vect, int k){
    std::cout << "Amount of elements, bigger than "<<k<<": ";
    std::cout << count_if(vect.begin(), vect.end(), [k](int i){return i > k;});
    std::cout <<'\n';
}
void printAmountOfElements(std::vector<int> &vect){
    std::cout << "Amount of numbers: " << vect.size() <<'\n';
}
void printSum(std::vector<int> &vect){
    std::cout << "Sum: " << accumulate(vect.begin(), vect.end(), 0) << '\n';
}
void printAverage(std::vector<int> &vect){
    std::cout << "Average: " <<(double) accumulate(vect.begin(), vect.end(), 0) / vect.size() <<'\n';
}
void getWordsStartWith(std::vector<std::string> &dest, const std::vector<std::string> &src, char c){
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
void countWordRepeats(std::map<std::string, int> &dest, const std::vector<std::string> &src){
    std::for_each(src.begin(), src.end(), [&dest](std::string str){ dest[str]++;});
}


int countStudentsWithMark(std::vector<Student> students, double mark){
    std::count_if(students.begin(), students.end(), [mark](Student st){ return st.mark == mark;});
}
