#include "practice6.h"
bool isCorrectInputFile(ifstream &_fin){
    if(_fin &&  _fin.peek() != ifstream::traits_type::eof()){
        return true;
    } else {
        cout << "Input file doesn't exist or empty" << endl;
        return false;
    }
}
bool isPalindromeRecursion(char*str,int i, int j){
    if(str[i] != str[j]){
        return false;
    } else {
        return (j - i < 2) ? true : isPalindromeRecursion(str, i+1, j-1);
    }
}
bool isPalindrome(char * str, int i, int j){
    int length = strlen(str);
    if(i < 0 || j < 0 || i >= length || j >= length){
        return false;
    }else if(i == j){
        return true;
    } else if(i > j){
        int temp = i;
        i = j;
        j = temp;
        return isPalindromeRecursion(str, i, j);
    }
}
int digitalRootRecursion(int a){
    if(a < 10){
        return a;
    } else {
        int sum = 0;
        while(a > 0){
            sum += a % 10;
            a/=10;
        }
        digitalRootRecursion(sum);
    }
}
int digitalRoot(int a){
    if(a < 1){
        return -1;
    } else {
        return digitalRootRecursion(a);
    }
}
int AckermannFunctionRecursion(int n, int m){
    if(n == 0){
        return m+1;
    } else if(n != 0 && m == 0){
        return AckermannFunctionRecursion(n - 1, 1);
    } else if(n > 0 && m > 0){
        return AckermannFunctionRecursion(n - 1, AckermannFunctionRecursion(n, m - 1));
    }
}
int AckermannFunction(int n, int m){
    if(n > 0 && m > 0){
        return AckermannFunctionRecursion(n, m);
    } else {
        return -1;
    }
}
