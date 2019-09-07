#include "trainService.h"
TrainService::TrainService()
{
}
TrainService::TrainService(vector<Train> trains)
{
    this->trains = trains;
}
vector<Train> TrainService::sortByTime(int sortOrder)
{
    vector<Train> result(trains);
    sort(result.begin(), result.end(), [ ]( Train& t1,  Train& t2 )
        {
           return t1.getDepartureTime().inMinutes() < t2.getDepartureTime().inMinutes();
        });
    if(sortOrder == TrainService::DESC_SORT)
    {
        reverse(result.begin(), result.end());
    }
    return result;
}
vector<Train> TrainService::sortByDestination(int sortOrder)
{
    vector<Train> result(trains);
    sort(result.begin(), result.end(), [ ]( Train& t1,  Train& t2 )
        {
           return t1.getDestination().compare(t2.getDestination()) < 0;
        });
    if(sortOrder == TrainService::DESC_SORT)
    {
        reverse(result.begin(), result.end());
    }
    return result;
}
vector<Train> TrainService::getTrainsByDestination(string destination)
{
    vector<Train> result;
    int length = trains.size();
    for(int i = 0; i < length; i++)
    {
        if(trains[i].getDestination() == destination)
        {
            result.push_back(trains[i]);
        }
    }
    return result;
}
vector<Train> TrainService::getTrainsDepartsAfter(HMTime time)
{
    vector<Train> result;
    int length = trains.size();
    for(int i = 0; i < length; i++)
    {
        if(trains[i].getDepartureTime().inMinutes() >= time.inMinutes())
        {
            result.push_back(trains[i]);
        }
    }
    return result;
}

