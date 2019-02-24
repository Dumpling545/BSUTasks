#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

#include <map>
#include <iterator>
#include <string>
#include <utility>
#include "include/busrouteinfo.h"

using namespace std;
/**

*/
vector<string> getDriversByRoute(multimap<string, BusRouteInfo> r_map, int route){
    vector<pair<string,BusRouteInfo>> temp;
    set<string> result;
    vector<string> vector_res;
    copy_if(r_map.begin(), r_map.end(), inserter(temp, temp.begin()), [route]  (pair<string, BusRouteInfo> r) {return r.second.routeNumber == route;});
    transform(temp.begin(), temp.end(), inserter(result, result.begin()), [](pair<string, BusRouteInfo> r) { return r.second.driver;});
    copy(result.begin(), result.end(), std::back_inserter(vector_res));
    return vector_res;
}
vector<string> getBusesByRoute(multimap<string, BusRouteInfo> r_map, int route){
    vector<pair<string,BusRouteInfo>> temp;
    vector<string> result;
    copy_if(r_map.begin(), r_map.end(), inserter(temp, temp.begin()), [route]  (pair<string, BusRouteInfo> r) {return r.second.routeNumber == route;});
    transform(temp.begin(), temp.end(), inserter(result, result.begin()), [](pair<string, BusRouteInfo> r) { return to_string(r.second.busNumber) + " " + r.second.busBrand;});
    return result;
}
void setBusInfo(multimap<string, BusRouteInfo>::iterator& pos, int busNumber, string busBrand){
    (*pos).second.busNumber = busNumber;
    (*pos).second.busBrand = busBrand;
}
void deleteInfo(multimap<string, BusRouteInfo> r_map, multimap<string, BusRouteInfo>::iterator& pos){
    r_map.erase(pos);
}
int getRouteByDriver(multimap<string, BusRouteInfo> r_map, string driver){
    int route = (*find_if(r_map.begin(), r_map.end(), [driver](pair<string, BusRouteInfo> r) {return r.first == driver;})).second.routeNumber;
    return route;
}
int countBusBrands(multimap<string, BusRouteInfo> r_map){
    set<string> temp;
    transform(r_map.begin(), r_map.end(), inserter(temp, temp.begin()), [](pair<string, BusRouteInfo> r) { return r.second.busBrand;});
    //unique(temp.begin(), temp.end());
    return temp.size();
}
template<class T>
void printVector(vector<T> vect, string divider = "\n"){
    for(int i = 0; i < vect.size(); i++){
        cout << vect[i] << divider;
    }
}
int main()
{
    vector<BusRouteInfo> routes;
    multimap<string, BusRouteInfo> routes_map;
    int n;
    cout << "Enter size: " << endl;
    cin >> n;
    for(int i = 0; i < n; i++){
        BusRouteInfo temp;
        cin >> temp;
        routes.push_back(temp);
        routes_map.insert(make_pair(temp.driver, temp));
    }
    sort(routes.begin(), routes.end(), [] (BusRouteInfo a,BusRouteInfo b) {return a.busNumber <= b.busNumber;});
    int number;
    cout << "Enter route of bus: " << endl;
    cin >> number;
    cout << "Drivers of route " <<number << ":" << endl;
    printVector<string>(getDriversByRoute(routes_map, number));
    cout << endl << "Buses of route " <<number << ":" << endl;
    printVector<string>(getBusesByRoute(routes_map, number));
    string driver;
    cout << endl<< "Enter name of driver: " << endl;
    cin >> driver;
    cout << "Route of driver " <<driver << ": " << getRouteByDriver(routes_map, driver) << endl;
    cout << endl<< "Amount of different bus brands: " <<countBusBrands(routes_map)<< endl;
    return 0;
}
