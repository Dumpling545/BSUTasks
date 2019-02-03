#include <iostream>
#include <cstring>
using namespace std;
template <typename T> T minimum(T  a, T b)

{	return (a<b)?a:b;         }

template <char*>  minimum(char*  a, char* b)

{	return strcmp(a,b)<0?a:b; }
int main()
{
    cout << minimum("char", "char*") << endl;
    return 0;
}
