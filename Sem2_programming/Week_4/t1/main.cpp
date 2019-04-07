#include <windows.h>
#include <winuser.h>
#include <iostream>
using namespace std;
int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR str, int n){
	TCHAR word[50];
	sprintf(word, "%s is entered", str);
	MessageBox(NULL, word, "Caption", MB_DEFBUTTON1);
	return 0;
}
