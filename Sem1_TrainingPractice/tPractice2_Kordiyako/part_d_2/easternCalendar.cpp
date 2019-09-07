#include <iostream>
#include <string>
/**
    В восточном календаре принят 60-летний цикл, состоящий из 12-летних подциклов,
    обозначаемых названиями цвета: зеленый, красный, желтый, белый и черный.
    В каждом подцикле годы носят названия животных: крысы, коровы, тигра, зайца,
    дракона, змеи, лошади, овцы, обезьяны, курицы, собаки и свиньи.
    По номеру года вывести его название, если 1984 год был началом цикла — годом зеленой крысы.

    Input           Output
    -------------------------------------------------------------------
    -1              Incorrect year(cannot be negative). Please re-enter:

    360            год чёрной обезьяны

    1983            год чёрной свиньи

    1984            год зелёной крысы

    1986            год зелёного тигра

    1997            год красной коровы

    1999            год красного зайца

    2012            год жёлтого дракона

    2014            год жёлтой лошади

    2025            год белой змеи

    2027            год белой овцы



*/
using namespace std;
enum Gender {female = 0, male};
string getYearName(int year){
    int cycleYear = 0;
    const int START_YEAR = 1984;
    const string YEAR_WORD = "год";
    const string COLORS[] = {"зелён","красн","жёлт", "бел", "чёрн"};
    const string GENDER_COLOR_SUFFIX[] = {"ой","ого"};
    const string ANIMALS[] = {"крысы", "коровы", "тигра", "зайца",
    "дракона", "змеи", "лошади", "овцы", "обезьяны", "курицы", "собаки","свиньи"};
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
