#include "include/practice2.h"
#include "student.h"
using namespace std;
ifstream fin("input.txt");
int main()
{
    if(isCorrectInputFile(fin)){
        vector<Student> students;
        fillVector<Student>(fin, students);
        double mark;
        enterElement<double>(mark, "mark");
        cout << "Amount of students with mark " << mark << ": ";
        cout << countStudentsWithMark(students, mark) << '\n';
        int group;
        enterElement<int>(group, "group");
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
    }
    return 0;
}
