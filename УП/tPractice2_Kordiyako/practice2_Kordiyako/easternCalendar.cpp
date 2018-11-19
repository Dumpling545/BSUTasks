#include <iostream>
#include <string>
/**
    � ��������� ��������� ������ 60-������ ����, ��������� �� 12-������ ���������,
    ������������ ���������� �����: �������, �������, ������, ����� � ������.
    � ������ �������� ���� ����� �������� ��������: �����, ������, �����, �����,
    �������, ����, ������, ����, ��������, ������, ������ � ������.
    �� ������ ���� ������� ��� ��������, ���� 1984 ��� ��� ������� ����� � ����� ������� �����.

    Input           Output
    -------------------------------------------------------------------
    -1              Incorrect year(cannot be negative). Please re-enter:

    360            ��� ������ ��������

    1983            ��� ������ ������

    1984            ��� ������ �����

    1986            ��� ������� �����

    1997            ��� ������� ������

    1999            ��� �������� �����

    2012            ��� ������ �������

    2014            ��� ����� ������

    2025            ��� ����� ����

    2027            ��� ����� ����



*/
using namespace std;
enum Gender {female = 0, male};
string getYearName(int year){
    int cycleYear = 0;
    const int START_YEAR = 1984;
    const string YEAR_WORD = "���";
    const string COLORS[] = {"����","�����","���", "���", "����"};
    const string GENDER_COLOR_SUFFIX[] = {"��","���"};
    const string ANIMALS[] = {"�����", "������", "�����", "�����",
    "�������", "����", "������", "����", "��������", "������", "������","������"};
    const Gender ANIMAL_GENDER[] = {female, female, male, male, male, female, female, female, female, female, female, female};
    cycleYear = (year - 1984) % 60;
    if(year < 1984){
        cycleYear += 60;
    }
    int animalIndex = cycleYear % 12;
    int animalGender = ANIMAL_GENDER[animalIndex];
    return YEAR_WORD + " " + COLORS[cycleYear/12] + GENDER_COLOR_SUFFIX[animalGender] + " " + ANIMALS[animalIndex];
}
int main()
{
    int n;
    setlocale(LC_ALL, "Russian");
    cout << "Enter year:" << endl;
    cin >> n;
    while(n < 0){
        cout << "Incorrect year(cannot be negative). Please re-enter: " << endl;
        cin >> n;
    }
    cout << getYearName(n)<<endl;
    system("pause");
    return 0;
}
