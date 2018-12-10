#include "set.h"

Set::Set()
{
    elements = new char[MAX_LENGTH];
    clear();
}
Set::Set(const Set& set) : Set(){
    for(int i = 0; set.elements[i] != '\0' && i < 256; i++){
        elements[i] = set.elements[i];
    }
}
Set::Set(std::vector<char> set){
    init(set);
}
Set::~Set()
{
    delete [] elements;
}
int Set::findEqualOrPrevious(const char c) const{
    int rborder = 0;
    int lborder = Set::MAX_LENGTH - 1;
    while(lborder - rborder > 1){
        int avg = (rborder + lborder)/2;
        if(elements[avg] >= c){
            rborder = avg;
        } else {
            lborder = avg;
        }
    }
    return rborder;
}
void Set::addElement(char element){
    int rborder = findEqualOrPrevious(element);
    if(elements[rborder] != element){
        for(int i = Set::MAX_LENGTH - 1; i > rborder + 1; i--){
            elements[i] = elements[i-1];
        }
        elements[rborder + 1] = element;
    }
}
void Set::removeElement(char element){
    int rborder = findEqualOrPrevious(element);
    if(elements[rborder] == element){
        for(int i = rborder; i < Set::MAX_LENGTH - 1; i++){
            elements[i] = elements[i+1];
        }
    }
}
int Set::getCardinality() const{
    int i = 0;
    int rborder = findEqualOrPrevious(1);
    return rborder+1;
}
std::ostream& operator<<(std::ostream &stream, const Set& set){
    int length = set.getCardinality();
    stream<<'{';
    for(int i = 0; i < length-1; i++){
        stream << set.elements[i] <<"  ";
    }
    stream << set.elements[length-1] <<"}";
    return stream;
}
std::istream& operator>>(std::istream& stream, Set& set){
    std::vector<char> temp;
    char c;
    std::string input;
    std::getline(stream, input);
    int length = input.size();
    for(int i = 0; i < length; i++){
        temp.push_back(input[i]);
    }
    set.clear();
    set.init(temp);
    return stream;
}
void Set::init(const std::vector<char> set){
    std::vector<char> temp(set);
    //delete duplicates
    std::sort(temp.begin(), temp.end());
    std::reverse(temp.begin(), temp.end());
    temp.erase(unique( temp.begin(), temp.end() ), temp.end());
    int length = temp.size();
    for(int i = 0; i < length; i++){
        elements[i] = temp[i];
    }
    for(int i = length; i < Set::MAX_LENGTH; i++){
        elements[i] = '\0';
    }
    std::vector<char>().swap(temp);
}
const Set Set::operator+(const Set& rn) const{
    Set set = Set();
    int i = 0;
    int j = 0;
    int length_i = getCardinality();
    int length_j = rn.getCardinality();
    int k = 0;
    while(i < length_i && j < length_j){
        if(elements[i] > rn.elements[j]){
            set.elements[k] = elements[i];
            i++;
        } else if(elements[i] < rn.elements[j]){
            set.elements[k] = rn.elements[j];
            j++;
        } else {
            set.elements[k] = elements[i];
            i++;
            j++;
        }
        k++;
    }
    return set;
}
const Set Set::operator*(const Set& rn) const{
    Set set = Set();
    int i = 0;
    int j = 0;
    int length_i = getCardinality();
    int length_j = rn.getCardinality();
    int k = 0;
    while(i < length_i && j < length_j){
        if(elements[i] > rn.elements[j]){
            i++;
        } else if(elements[i] < rn.elements[j]){
            j++;
        } else {
            set.elements[k++] = elements[i];
            i++;
            j++;
        }
    }

    return set;
}
const Set Set::operator-(const Set& rn) const{
    Set set = Set(*this);
    Set intersection = (*this)*rn;
    int is_length = intersection.getCardinality();
    for(int i = 0; i < is_length; i++){
        set.removeElement(intersection.elements[i]);
    }
    return set;
}
void Set::clear(){
    for(int i = 0; i < Set::MAX_LENGTH; i++){
        elements[i] = '\0';
    }
}
const Set Set::operator=(const Set& rn){
    clear();
    init(std::vector<char>(rn.elements, rn.elements + rn.getCardinality()));
}
const bool Set::operator==(const Set& rn) const{
    int length = getCardinality();
    if(length == rn.getCardinality()){
        bool isEqual = true;
        for(int i = 0; i < length && isEqual; i++){
            isEqual = (elements[i] == rn.elements[i]);
        }
        return isEqual;
    } else {
        return false;
    }
}
const bool Set::operator!=(const Set& rn) const{
    return !((*this) == rn);
}
const bool Set::operator>=(const Set& rn) const{
    int containerLength = getCardinality();
    int contentLength = rn.getCardinality();
    if(containerLength < contentLength){
        return false;
    } else {
        int j = 0;
        int i = 0;
        bool include = true;
        while(i < containerLength && j < contentLength){
            if(elements[i] == rn.elements[j]){
                i++;
                j++;
            } else if(elements[i] > rn.elements[j]){
                i++;
            } else{
                include = false;
                break;
            }
        }
        return include;
    }
}
const bool Set::operator<=(const Set& rn) const{
    int containerLength = rn.getCardinality();
    int contentLength = getCardinality();
    if(containerLength < contentLength){
        return false;
    } else {
        int j = 0;
        int i = 0;
        bool include = true;
        while(i < containerLength && j < contentLength){
            if(rn.elements[i] == elements[j]){
                i++;
                j++;
            } else if(rn.elements[i] > elements[j]){
                i++;
            } else{
                include = false;
                break;
            }
        }
        return include;
    }
}
