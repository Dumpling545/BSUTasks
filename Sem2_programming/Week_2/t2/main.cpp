#include "student.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <string>
#include <utility>
#include <numeric>
/**
    В каждой строке исходного файла задается следующая информация о студенте

        фамилия-№группы-оценки за сессию

        1.Вводом из текстового файла сформировать vector из объектов «студент».
        2.Выполнить сортировку объектов «студент» в контейнере.
        3.Реализовать операцию удаления «студента», фамилия которого вводится с консоли.
        4.Сформировать map из полученного ранее контейнера, используя ключ - фамилия.
        5.Найти всех студентов, не сдавших сессию.
        6.Найти студента из указанной группы с максимальной суммой баллов.

    Зам. Используйте стандартные алгоритмы

*/
using namespace std;
ifstream fin("input.txt");
int main()
{
    const int NOT_LESS_THAN = 4;
    string line;
    vector<Student> students;
    Student temp;
    while (getline(fin, line))
    {
        istringstream iss(line);
        iss>>temp;
        students.push_back(temp);
        temp.examsResult.clear();
    }
    sort(students.begin(), students.end(), [] (Student a,Student b) {return a.name <= b.name;});
    for(int i = 0; i < students.size(); i++){
        cout <<students[i]<<endl;
    }
    cout << "Student to delete: " << endl;
    string removeName;
    cin >> removeName;
    students.erase(
        remove_if(students.begin(), students.end(), [removeName] (Student s) {return s.name == removeName;}),
        students.end());
    cout << endl;
        for(int i = 0; i < students.size(); i++){
            cout <<students[i]<<endl;
        }
        map<string, Student> student_map;
        for(int i = 0; i < students.size(); i++){
            student_map[students[i].name] = students[i];
        }
        cout << "Students that has successfully passed session:" << endl;
        for_each(student_map.begin(), student_map.end(), [NOT_LESS_THAN] (pair<string, Student> s) {
                 string passExams = s.second.name;
                 passExams.push_back('\n');
                 for(int i = 0; i < s.second.examsResult.size(); i++){
                    if(s.second.examsResult[i] < NOT_LESS_THAN){
                        passExams.clear();
                        break;
                    }
                 }
                 cout << passExams;

        });
        cout << "Choose group to see the first by rating in group:" << endl;
        int group = 0;
        cin >> group;
        int maxSum = 0;
         cout << "First students by rating in "<< group <<" group:" << endl;
        for_each(student_map.begin(), student_map.end(), [group, &maxSum] (pair<string, Student> s) {
                 if(s.second.group == group){
                    int sum = accumulate(s.second.examsResult.begin(), s.second.examsResult.end(), 0);
                    if(maxSum < sum){
                        maxSum = sum;
                    }
                 }
        });
        for_each(student_map.begin(), student_map.end(), [group, maxSum](pair<string, Student> s) {
                 if(s.second.group == group){
                    int sum = accumulate(s.second.examsResult.begin(), s.second.examsResult.end(), 0);
                    if(maxSum == sum){
                        cout << s.second.name << endl;
                    }
                 }
        });
    return 0;
}
