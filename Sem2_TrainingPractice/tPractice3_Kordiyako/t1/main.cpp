#include <iostream>
#include <fstream>
#include "flowerbed.h"
#include "week3.h"
#include <list>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>

/**
    � ����� ����������� ��������� ������ � ��������� ������� (� ������� ��� ������������ �������)
        �������   �������������� ����� ������   �������� (vector) �������, �������� �� ������.
    (1) ���������� ������ � ���������������� ���������� (� ������� 1, ��. ������� 1).
    (2) ��������� ���������� �� �������������� ����� ������. ����� ����� ����: �������, ����������, ����


*/
using namespace std;
ofstream fout("output.txt");
ifstream fin("input.txt");
int main()
{
    std::list<Flowerbed> flowerbeds;
    fillList(fin, flowerbeds);
    fout << "A. Flowerbeds sorted by shape: " << endl;
    sortByShape(flowerbeds);
    printInterval<Flowerbed>(fout, flowerbeds.begin(), flowerbeds.end());

    map<int, Flowerbed> m_flowerbeds;
    convertListToMap(flowerbeds, m_flowerbeds);
    fout << "B. Unique shapes of flowerbeds: " << endl;
    set<string> shapes;
    getUniqueShapes(m_flowerbeds, shapes);
    printInterval<string>(fout, shapes.begin(), shapes.end());

    int id;
    enterElement<int>(id, "flowerbed id");

    fout << endl <<"C. Flowers of the Flowerbed #"<<id <<": "<<endl;

    map<int, Flowerbed>::iterator it = m_flowerbeds.find(id);
    if(it == m_flowerbeds.end()){
        fout << "   Flowerbed #" << id << " doesn't exist" << endl;
    } else {
        if((*it).second.flowers.empty()){
            fout << "   Flowerbed #" << id << " doesn't have any flowers" << endl;
        } else {
            for(set<string>::iterator flow_it = (*it).second.flowers.begin();
            flow_it != (*it).second.flowers.end(); flow_it++){
                fout << "   �"<<(*flow_it)<<endl;
            }
        }
    }
    fout << endl << "D. Unique flowers: " <<endl;
    set<string> flowers;
    for_each(m_flowerbeds.begin(), m_flowerbeds.end(), [&flowers](pair<int, Flowerbed> p) { flowers.insert(p.second.flowers.begin(),p.second.flowers.end());});
    for(set<string>::iterator it = flowers.begin(); it != flowers.end(); it++){
        fout << "   �"<<*it << endl;
    }
    fout << endl <<"E. Group flowerbeds by sets of flower: " << endl;
    multimap<set<string>, int, setStringComparator> group_by_flowers;
    for(map<int, Flowerbed>::iterator it = m_flowerbeds.begin(); it != m_flowerbeds.end(); it++){
        group_by_flowers.insert(make_pair((*it).second.flowers, (*it).second.id));
    }
    for(multimap<set<string>, int, setStringComparator>::iterator it = group_by_flowers.begin();
    it != group_by_flowers.end();){
        multimap<set<string>, int, setStringComparator>::iterator curr = it;
        fout << "   Flowersets ";
        while (it != group_by_flowers.end() && it->first == curr->first){
            fout <<" #" << it->second << " ";
            ++it;
        }
        fout<<"have equal set of flowers: "<<endl;
        for(set<string>::iterator set_it = curr->first.begin(); set_it != curr->first.end(); set_it++){
            fout << "      �" << *set_it << endl;
        }
    }
     fout << endl <<"F. Flowerbed with max amount of flowers: ";
    it = max_element(m_flowerbeds.begin(), m_flowerbeds.end(),
                [] (pair<int, Flowerbed> p1, pair<int, Flowerbed> p2){
                    return p1.second.flowers.size() < p2.second.flowers.size();
                });
    fout<<"#"<<it->second.id <<endl;
    int types;
    cout <<"Enter amount of flowertypes: "<<endl;
    cin >> types;
    fout << endl <<"G. Flowerbeds with "<< types<<" types of flowers: ";
    map<int, Flowerbed> with_n_types;
    copy_if(m_flowerbeds.begin(), m_flowerbeds.end(), inserter(with_n_types, with_n_types.begin()),
            [types](pair<int, Flowerbed> p) { return p.second.flowers.size() == types;});
    if(with_n_types.size() == 0){
        fout << "<no such flowerbeds>" <<endl;
    } else {
        for(map<int, Flowerbed>::iterator iter = with_n_types.begin(); iter != with_n_types.end(); iter++){
                fout<<"#"<< iter->first << " ";
        }
    }
    fout << endl <<"H. Flowerbed with 1 type of flowers: ";
    it = find_if(m_flowerbeds.begin(), m_flowerbeds.end(),
                 [](pair<int, Flowerbed> p) {return p.second.flowers.size() == 1;});
    if(it == m_flowerbeds.end()){
        fout << "<no such flowerbeds>" <<endl;
    } else {
        fout <<"#" <<it->first <<endl;
    }
    fout << endl <<"I. Flower(s) on each flowerbed: "<<endl;
    set<string> intersection = flowers;
    set<string> temp;
    for(map<int, Flowerbed>::iterator iter = m_flowerbeds.begin(); iter != m_flowerbeds.end(); iter++){
        set_intersection(intersection.begin(), intersection.end(),
                        iter->second.flowers.begin(), iter->second.flowers.end(),
                        inserter(temp, temp.begin()));
        intersection.clear();
        intersection = temp;
        temp.clear();
    }
    if(intersection.size() == 0){
        fout << "    <no such flowers>" <<endl;
    } else {
        for(set<string>::iterator iter = intersection.begin(); iter != intersection.end(); iter++){
            fout << "   �" << *iter << endl;
        }
    }
    cout << "Enter name of flower: " <<endl;
    string flowername;
    cin >> flowername;
    fout << endl <<"J. Flowerbeds that don't have "<< flowername <<": ";
    map<int, Flowerbed> without_flower;
    copy_if(m_flowerbeds.begin(), m_flowerbeds.end(), inserter(without_flower, without_flower.begin()),
            [flowername](pair<int, Flowerbed> p) { return p.second.flowers.find(flowername) == p.second.flowers.end();});
    if(without_flower.size() == 0){
        fout << "<no such flowerbeds>" <<endl;
    } else {
        for(map<int, Flowerbed>::iterator iter = without_flower.begin(); iter != without_flower.end(); iter++){
                fout<<"#"<< iter->first << " ";
        }
    }
    fout << endl <<"K. Amount of flowers on circle-shaped flowerbeds: ";
    //TO DO
    fout << endl <<"L. Delete flower "<<flowername <<" from all flowerbeds";
    //TO DO
    fout << endl <<"M. Find flowerbed with n flowers: ";
    //TO DO
    fout << endl <<"N. Find all flowerbeds with shape 'x': ";
    //TO DO
    return 0;
}
