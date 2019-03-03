#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;
/**
    ������������ ��������� � ���������� ���� string � �������� ��� ����.
        � ����� ������� ���� ���������� �����.
    N ������� ������� ����������, �������������� ��������� �� ��������� �����.
    ������� � ���� ����������:
        -����� ���� ��� ���� � ������� ������;
        -��� ����� ����� ������� ���� �� ���� �����;
        -����� ���� ���� � �����, �� �� � ����� ������ �� �������.
    �� ������� ����� ������������ ��������� ����������:

1)	��� ������� � �����;

2)	���� ������� ������, � ������� ����� �������������� ��������� ����������� ������ ����
*/
ofstream fout("output.txt");
ifstream fin("input.txt");
int main()
{
    set<string> fish;
    vector<set<string>> fishermen;
    string strline, str;
    stringstream str_stream;
    setlocale(LC_ALL, "Russian");
    ws(fin);
    getline(fin, strline);
    str_stream << strline;
    while(str_stream >> str){
        fish.insert(str);
    }
    str_stream.clear();
    while(!fin.eof()){
        ws(fin);
        getline(fin, strline);
        str_stream << strline;
        set<string> s;
        while(str_stream >> str){
            s.insert(str);
        }
        fishermen.push_back(s);
        str_stream.clear();
    }
    set<string> intersection = fishermen[0];
    set<string> temp;
    for(int i = 1; i < fishermen.size(); i++){
        set_intersection(intersection.begin(), intersection.end(),
                        fishermen[i].begin(), fishermen[i].end(),
                        inserter(temp, temp.begin()));
        intersection.clear();
        intersection = temp;
        temp.clear();
    }
    fout << "� ������� ������ ����:" << endl;
    for(set<string>::iterator it = intersection.begin(); it != intersection.end(); it++){
        fout << *it << endl;
    }
    set<string> s_union = fishermen[0];
    for(int i = 1; i < fishermen.size(); i++){
        set_union(s_union.begin(), s_union.end(),
                        fishermen[i].begin(), fishermen[i].end(),
                        inserter(temp, temp.begin()));
        s_union.clear();
        s_union = temp;
        temp.clear();
    }
    fout << "���� �� � ������ ������ ����:" << endl;
    for(set<string>::iterator it = s_union.begin(); it != s_union.end(); it++){
        fout << *it << endl;
    }
    set<string> difference;
    set_difference(fish.begin(), fish.end(),
                        s_union.begin(), s_union.end(),
                        inserter(difference, difference.begin()));
    fout << "�� � ������ ������ ���:" << endl;
    for(set<string>::iterator it = difference.begin(); it != difference.end(); it++){
        fout << *it << endl;
    }
    return 0;
}
