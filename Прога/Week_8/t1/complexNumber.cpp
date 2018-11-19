#include "complexNumber.h"

ComplexNumber::ComplexNumber()
{
    real = 0;
    imaginary = 0;
}
ComplexNumber::ComplexNumber(const ComplexNumber &source){
    real = source.real;
    imaginary = source.imaginary;
}
ComplexNumber::ComplexNumber(double real, double imaginary){
    this->real = real;
    this->imaginary = imaginary;
}
ComplexNumber ComplexNumber::operator+=(const ComplexNumber& cn){
    real+=cn.real;
    imaginary +=cn.imaginary;
    return *this;
}
ComplexNumber ComplexNumber::operator-=(const ComplexNumber& cn){
    real-=cn.real;
    imaginary -=cn.imaginary;
    return *this;
}
ComplexNumber ComplexNumber::operator*=(const ComplexNumber& cn){
    real = real*cn.real - imaginary*cn.imaginary;
    imaginary = real*cn.imaginary + imaginary*cn.real;
    return *this;
}
ComplexNumber ComplexNumber::operator/=(const ComplexNumber& cn){
    if(cn.real == 0 && cn.imaginary == 0){
        throw "Division by zero!";
    } else {
        double temp = cn.real*cn.real + cn.imaginary*cn.imaginary;
        real = (real*cn.real + imaginary*cn.imaginary)/temp;
        imaginary = (imaginary * cn.real - real * cn.imaginary)/temp;
        return *this;
    }
}
const ComplexNumber ComplexNumber::operator+(const ComplexNumber& cn) const{
    return ComplexNumber(*this)+= cn;
}
const ComplexNumber ComplexNumber::operator-(const ComplexNumber& cn) const{
    return ComplexNumber(*this)-= cn;
}
const ComplexNumber ComplexNumber::operator*(const ComplexNumber& cn) const{
    return ComplexNumber(*this)*= cn;
}
const ComplexNumber ComplexNumber::operator/(const ComplexNumber& cn) const{
    return ComplexNumber(*this)/= cn;
}
const ComplexNumber ComplexNumber::operator=(const ComplexNumber& cn){
    real = cn.real;
    imaginary = cn.imaginary;
    return *this;
}
const bool ComplexNumber::operator==(const ComplexNumber& cn) const{
    return real == cn.real && imaginary == cn.imaginary;
}
const bool ComplexNumber::operator!=(const ComplexNumber& cn) const{
    return !((*this) == cn);
}
double ComplexNumber::abs() const {
    return sqrt((real*real) + (imaginary * imaginary));
}
 const bool ComplexNumber::operator>(const ComplexNumber& cn) const{
    return abs() > cn.abs();
}
const bool  ComplexNumber::operator<(const ComplexNumber& cn) const{
    return abs() < cn.abs();
}
const bool ComplexNumber::operator<=(const ComplexNumber& cn) const{
    return abs() <= cn.abs();
}
const bool ComplexNumber::operator>=(const ComplexNumber& cn) const{
    return abs() >= cn.abs();
}
void ComplexNumber::print(ostream& os) const {
    os << "[";
    if(real!= 0 || imaginary == 0){
    os << real;
    }
    if(real == 0){
        os << imaginary <<"i";
    } else if(imaginary > 0){
        os << " + " << imaginary<<"i";
    } else if(imaginary < 0){
        os << " - " << -1.0*imaginary<<"i";
    }
    os << "]";
}
void ComplexNumber::get(istream& is){
    is >> real >> imaginary;
}
