#pragma once
#include <exception>
#include <cmath>
#include <iostream>
using namespace std;
class ComplexNumber
{
    public:
        double real;
        double imaginary;
        ComplexNumber();
        ComplexNumber(const ComplexNumber &source);
        ComplexNumber(double real, double imaginary);
        ComplexNumber operator+=(const ComplexNumber& cn);
        ComplexNumber operator-=(const ComplexNumber& cn);
        ComplexNumber operator*=(const ComplexNumber& cn);
        ComplexNumber operator/=(const ComplexNumber& cn);
        const ComplexNumber operator+(const ComplexNumber& cn) const;
        const ComplexNumber operator-(const ComplexNumber& cn) const;
        const ComplexNumber operator*(const ComplexNumber& cn) const;
        const ComplexNumber operator/(const ComplexNumber& cn) const;
        const ComplexNumber operator=(const ComplexNumber& cn);
        const bool operator==(const ComplexNumber& cn) const;
        const bool operator!=(const ComplexNumber& cn) const;
        //compare by absolute value
        double abs() const;
        const bool operator>(const ComplexNumber& cn) const;
        const bool operator<(const ComplexNumber& cn) const;
        const bool operator<=(const ComplexNumber& cn) const;
        const bool operator>=(const ComplexNumber& cn) const;
        void print(ostream& os) const;
        void get(istream& is);
};
