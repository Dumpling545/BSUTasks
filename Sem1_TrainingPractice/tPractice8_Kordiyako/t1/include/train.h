#pragma once
#include <string>
#include <iostream>
#include "hmtime.h"
using namespace std;
class Train
{
private:
    string destination;
    string id;
    HMTime departureTime;
public:
    Train();
    Train(const Train& train);
    Train(string id,string destination, HMTime departureTime);
    string getDestination() const;
    string getId() const;
    HMTime getDepartureTime() const;
    friend ostream& operator<<(ostream &stream, const Train& train);
    friend istream& operator>>(istream& stream, Train& train);
};
