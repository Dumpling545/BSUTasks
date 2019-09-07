#include "train.h"
HMTime Train::getDepartureTime() const
{
    return departureTime;
}
string Train::getDestination() const
{
    return destination;
}
string Train::getId() const
{
    return id;
}
Train::Train(){}
Train::Train(const Train& train){
    id = train.getId();
    destination = train.getDestination();
    departureTime = train.getDepartureTime();
}
Train::Train(string id, string destination, HMTime departureTime){
    this->id = id;
    this->destination = destination;
    this->departureTime = departureTime;
}
ostream& operator<<(ostream &stream, const Train& train)
{
   stream << train.getId() << " " << train.getDestination() << " " << train.getDepartureTime().get();
   return stream;
}
istream& operator>>(istream& stream, Train& train)
{
    string id, destination, time;
    stream>>id;
    stream>>destination;
    stream>> time;
    train = Train(id, destination, HMTime(time));
    return stream;
}
