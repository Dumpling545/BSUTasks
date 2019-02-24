#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iterator>
#include <set>
#include <map>
#include <cstring>
using namespace std;
ifstream fin("input.txt");
struct Student{
    char name[20];
    int group;
    double mark;
};
int main()
{
    vector<Student> students;
    char name[20];
    int group;
    double mark;
    Student s;
    while(fin >> name >> group >> mark){
        strcpy(s.name, name);
        s.group = group;
        s.mark = mark;
        students.push_back(s);
    }
    cout << "Enter mark: " <<endl;
    cin >> mark;
    cout << "Amount of students with mark " << mark << ": " << count_if(students.begin(), students.end(), [mark](Student st){ return st.mark == mark;});
    cout << endl << "Enter group: " <<endl;
    cin >> group;
    cout << "Students in group " << group << ": " <<endl;
    for_each(students.begin(), students.end(), [cout, group](Student st){ if(st.group == group)cout<<st.name<<endl; });
    vector<Student> reversed_students;
    copy(students.begin(), students.end(), inserter(reversed_students, reversed_students.begin()));
    reverse(reversed_students.begin(), reversed_students.end());
    cout << endl<<"Reversed order: " <<endl;
    for_each(reversed_students.begin(), reversed_students.end(), [cout](Student st){ cout << st.name << " "<<st.group << " " << st.mark << endl;});
    cout << endl<<"Sorted by name: " <<endl;
    sort(students.begin(), students.end(), [](Student a, Student b){return strcmp(a.name, b.name) < 0;});
    for_each(students.begin(), students.end(), [cout](Student st){ cout << st.name << " "<<st.group << " " << st.mark << endl;});
    cout << endl<<"Sorted by group: " <<endl;
    sort(students.begin(), students.end(), [](Student a, Student b){return a.group < b.group;});
    for_each(students.begin(), students.end(), [cout](Student st){ cout << st.name << " "<<st.group << " " << st.mark << endl;});
    cout << endl<<"Sorted by mark: " <<endl;
    sort(students.begin(), students.end(), [](Student a, Student b){return a.mark < b.mark;});
    for_each(students.begin(), students.end(), [cout](Student st){ cout << st.name << " "<<st.group << " " << st.mark << endl;});
    return 0;
}
