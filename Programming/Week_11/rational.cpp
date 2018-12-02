#include "rational.h"

Rational::Rational()
{
    numerator = 0;
    denominator =1;
}
Rational::Rational(const Rational& source){
    numerator = source.numerator;
    setDenominator(source.denominator);
    normalize();
}
Rational::Rational(long numerator, long denominator){
    this->numerator = numerator;
    setDenominator(denominator);
    normalize();
}
Rational Rational::operator+=(const Rational& rn){
    numerator = numerator*rn.denominator + denominator*rn.numerator;
    setDenominator(denominator*rn.denominator);
    normalize();
    return *this;
}
Rational Rational::operator-=(const Rational& rn){
    numerator = numerator*rn.denominator - denominator*rn.numerator;
    setDenominator(denominator*rn.denominator);
    normalize();
    return *this;
}
Rational Rational::operator*=(const Rational& rn){
    numerator = numerator*rn.numerator;
    setDenominator(denominator*rn.denominator);
    normalize();
    return *this;
}
Rational Rational::operator/=(const Rational& rn){
    numerator = numerator*rn.denominator;
    setDenominator(denominator*rn.numerator);
    normalize();
    return *this;
}
const Rational Rational::operator+(const Rational& rn) const{
    return Rational(*this)+= rn;
}
const Rational Rational::operator-(const Rational& rn) const{
    return Rational(*this)-= rn;
}
const Rational Rational::operator*(const Rational& rn) const{
    return Rational(*this)*= rn;
}
const Rational Rational::operator/(const Rational& rn) const{
    return Rational(*this)/= rn;
}
const Rational Rational::operator=(const Rational& rn){
    numerator = rn.numerator;
    setDenominator(rn.denominator);
    normalize();
    return *this;
}
const bool Rational::operator==(const Rational& rn) const{
    return numerator == rn.numerator && denominator == rn.denominator;
}
const bool Rational::operator!=(const Rational& rn) const{
    return !((*this) == rn);
}

 const bool Rational::operator>(const Rational& rn) const{
    Rational r((*this) - rn);
    return r.numerator*r.denominator > 0;
}
const bool  Rational::operator<(const Rational& rn) const{
    Rational r((*this) - rn);
    return r.numerator*r.denominator < 0;
}
const bool Rational::operator<=(const Rational& rn) const{
    return !((*this) > rn);
}
const bool Rational::operator>=(const Rational& rn) const{
    return !((*this) < rn);
}
void Rational::print(ostream& os) const {
    os << " " << numerator << "/" << denominator <<" ";
}
void Rational::get(istream& is){
    long n, d;
    is >> n >> d;
    numerator = n;
    setDenominator(d);
    normalize();
}
void Rational::normalize(){
    reduce();
    if(denominator < 0){
        denominator*=-1;
        numerator*=-1;
    }
}

long Rational::getNumerator() const{
    return numerator;
}
long Rational::getDenominator() const{
    return denominator;
}
void Rational::setDenominator(long value){
    if(value == 0){
        cout << "DIVISION BY ZERO!" << endl;
    } else {
        denominator = value;
    }
}
void Rational::setNumerator(long value){
    numerator = value;
}
void Rational::reduce(){
    long a = numerator;
    long b = denominator;
    long t = 0;
    while(b!=0){
        t = b;
        b = a % b;
        a = t;
    }
    numerator/=a;
    denominator/=a;
}

