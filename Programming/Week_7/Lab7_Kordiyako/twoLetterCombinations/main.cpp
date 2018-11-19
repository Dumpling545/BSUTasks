#include "week7.h"
/**Дана строка. Посчитать в ней частоты всех двухбуквенных
сочетаний без учета регистра и без учета символов, не являющихся буквами.
*/
using namespace std;
ofstream fout("output.txt");
ifstream fin ("input.txt");

int main()
{
    int n = 1000;
    char str[n];
    while(fin.getline(str, n)){
        printTwoLetterCombinations(fout, str);
        delete [] str;
    }
    system("pause");
    return 0;
}
