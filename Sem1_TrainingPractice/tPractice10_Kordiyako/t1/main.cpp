#include <iostream>
#include <string>
#include "sparsearr.h"
using namespace std;

int main()
{
    SparseArr<double> sa1(2000000);
    sa1[127649] = 1.1;
    sa1[38225] = 1.2;
    sa1[2004056] = 1.3;
    sa1[1999999] = 1.4;
    sa1.Show("sa1");
    cout << "sa1[38225] = " << sa1[38225] << endl;
    sa1[38225] = sa1[93];
    cout << "After the modification of sa1:\n";
    sa1.Show("sa1");
    SparseArr<string> sa2( 1000 );
    sa2[333] = "Nick";
    sa2[222] = "Peter";
    sa2[444] = "Ann";
    sa2.Show("sa2");
    sa2[222] = sa2[555];
    sa2.Show("sa2");
    return 0;
}
