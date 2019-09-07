#include <iostream>
#include <string>
/**
    Дано целое число в диапазоне от 100 до 999.
    Вывести строку —словесное описание данного числа,
    например: 256 — "двести пятьдесят шесть", 814 — "восемьсот четырнадцать".

    Input           Output
    -------------------------------------------------------------------
    99              Incorrect number(must be between 100 and 999).Please re-enter:

    1000            Incorrect number(must be between 100 and 999).Please re-enter:

    100             сто

    999             девятьсот девяносто девять

    212             двести двенадцать

    840             восемьсот сорок

    403             четыреста три

    551             пятьсот пятьдесят один
*/
using namespace std;

string getNumberName(int number){
    const string DIGITS[] = {"один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
    const string DOZENS_ONE[] ={"одиннадцать", "двенадцать","тринадцать", "четырнадцать",
                                "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};
    const string DOZENS_TWO_FOUR[] = {"двадцать", "тридцать","сорок"};
    const string HUNDREDS_TO_FOUR[] = {"сто", "двести", "триста", "четыреста"};
    const string HUNDRED_SUFFIX = "сот";
    const string DOZEN_SUFFIX = "десят";
    const string DOZEN_NINE = "девяносто";
    string result ="";
    int hundreds = number/100;
    int dozens = (number/10)% 10;
    int units = number % 10;
    switch(hundreds){
        case 1:
        case 2:
        case 3:
        case 4:
            result += HUNDREDS_TO_FOUR[hundreds - 1] + " ";
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            result += DIGITS[hundreds - 1] + HUNDRED_SUFFIX + " ";
    }
    switch(dozens){
        case 1:
            result += DOZENS_ONE[units-1];
            return result;
        case 2:
        case 3:
        case 4:
            result += DOZENS_TWO_FOUR[dozens-2] + " ";
            break;
        case 5:
        case 6:
        case 7:
        case 8:
            result += DIGITS[dozens-1] + DOZEN_SUFFIX + " ";
            break;
        case 9:
            result += DOZEN_NINE + " ";
            break;
    }
    if(units != 0) {
        result += DIGITS[units-1];
    }
    return result;
}
int main()
{
    int n;
    setlocale(LC_ALL, "Russian");
    cout << "Enter number:" << endl;
    cin >> n;
    while(n < 100 || n > 999){
        cout << "Incorrect number(must be between 100 and 999).Please re-enter:" << endl;
        cin>>n;
    }
    cout << getNumberName(n);
    system("pause");
    return 0;
}
