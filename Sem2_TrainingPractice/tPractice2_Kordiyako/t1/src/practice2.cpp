#include "practice2.h"
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
void fillVector(std::istream &_fin, std::vector<int> &vect){
    int elem;
    while(_fin >> elem){
        vect.push_back(elem);
    }
}

void printMax(std::vector<int> &vect){
    std::cout << "Max element: "<< *std::max_element(vect.begin(), vect.end()) << '\n';
}
void enterInteger(int &i){
    std::cout << "Enter element: " << '\n';
        std::cin >> i;
}
void printAmountOfElementsEqualTo(std::vector<int> &vect, int i){
    std::cout << "Amount of elements, equal to "<< i << ": " << std::count(vect.begin(), vect.end(), i) << '\n';
}
void printAmountOfElementsBiggerThan(std::vector<int> &vect, int k){
    std::cout << "Amount of elements, bigger than "<<k<<": " << count_if(vect.begin(), vect.end(), [k](int i){return i > k;}) <<'\n';
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
