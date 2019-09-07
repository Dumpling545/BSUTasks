#include "practice9.h"
int triangleType(int a, int b, int c){
/*Method returns -1, if triangle with such edges can't exist; 0, if all edges are different;
 1, if two edges are equivalent; 2, if all edges are equivalent*/
    long long d_a = a;
    long long d_b = b;
    long long d_c = c;
    if(d_a + d_b <= d_c || d_a + d_c <= d_b || d_b + d_c <= d_a){
        return -1;
    } else if(a == b || a == c || b == c){
        if(a == b && a == c){
            return 2;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}
