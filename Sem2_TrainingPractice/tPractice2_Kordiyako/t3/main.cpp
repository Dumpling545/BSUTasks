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
        std::vector<Student> studentsInGroup;
        getStudentsOfGroup(students, studentsInGroup, group);
        cout << "Students in group " << group << ": " <<endl;
        printInterval<Student>(studentsInGroup.begin(), studentsInGroup.end());

        vector<Student> reversedStudents;
        reverseStudents(students, reversedStudents);
        cout << endl<<"Reversed order: " <<endl;
        printInterval<Student>(reversedStudents.begin(),
                               reversedStudents.end());

        vector<Student> sortedByName;
        sortByName(students, sortedByName);
        cout << endl<<"Sorted by name: " <<endl;
        printInterval<Student>(sortedByName.begin(), sortedByName.end());

        vector<Student> sortedByGroup;
        sortByGroup(students, sortedByGroup);
        cout << endl<<"Sorted by group: " <<endl;
        printInterval<Student>(sortedByGroup.begin(), sortedByGroup.end());

        vector<Student> sortedByMark;
        sortByMark(students, sortedByMark);
        cout << endl<<"Sorted by mark: " <<endl;
        printInterval<Student>(sortedByMark.begin(), sortedByMark.end());
    }
    return 0;
}
