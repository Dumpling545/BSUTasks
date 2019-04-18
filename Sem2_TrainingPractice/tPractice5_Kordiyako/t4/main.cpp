#undef UNICODE
#include <windows.h>
#include "task4.h"
LPSTR input_str;
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
    input_str = lpCmdLine;
    MSG msg;
    if (!hPrevInstance){
        if (!InitApplication(hInstance)) return (FALSE);
    }
    if (!InitInstance(hInstance, nCmdShow)) return (FALSE);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (msg.wParam);
}
