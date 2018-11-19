#pragma once
#include <exception>
#include <cmath>
#include <iostream>
using namespace std;
class Rational
{
    public:
        Rational();
        Rational(const Rational &source);
        Rational(long numerator, long denominator);
        Rational operator+=(const Rational& rn);
        Rational operator-=(const Rational& rn);
        Rational operator*=(const Rational& rn);
        Rational operator/=(const Rational& rn);
        const Rational operator+(const Rational& rn) const;
        const Rational operator-(const Rational& rn) const;
        const Rational operator*(const Rational& rn) const;
        const Rational operator/(const Rational& rn) const;
        const Rational operator=(const Rational& rn);
        const bool operator==(const Rational& rn) const;
        const bool operator!=(const Rational& rn) const;
        void normalize();
        const bool operator>(const Rational& rn) const;
        const bool operator<(const Rational& rn) const;
        const bool operator<=(const Rational& rn) const;
        const bool operator>=(const Rational& rn) const;
        void print(ostream& os) const;
        void get(istream& is);
        long getNumerator() const;
        long getDenominator() const;
        void setNumerator(long value);
        void setDenominator(long value);
    private:
        long numerator;
        long denominator;
        void reduce();
};
