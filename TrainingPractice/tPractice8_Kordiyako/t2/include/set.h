#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
class Set
{
    public:
        Set();
        ~Set();
        Set(const Set& set);
        Set(std::vector<char> set);

        void addElement(char element);
        void removeElement(char element);
        void clear();
        int getCardinality() const;
        static const int MAX_LENGTH = 256;

        friend std::ostream& operator<<(std::ostream &stream, const Set& set);
        friend std::istream& operator>>(std::istream& stream, Set& set);

        const Set operator+(const Set& rn) const;
        const Set operator-(const Set& rn) const;
    const Set operator*(const Set& rn) const;
        const Set operator=(const Set& rn);
        const bool operator==(const Set& rn) const;
        const bool operator!=(const Set& rn) const;
        const bool operator>=(const Set& rn) const;
        const bool operator<=(const Set& rn) const;
    private:
        void init(const std::vector<char> set);
        char * elements;
        int findEqualOrPrevious(const char c) const;
};
