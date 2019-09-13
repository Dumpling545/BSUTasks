#include "task1.h"
Set<int> set1, set2;
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_COMMAND:
            switch(LOWORD(wParam)){
                case ID_REFRESH:
                    break;
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hDlg);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return TRUE;
            break;
    }
    return FALSE;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow){
    HWND hDlg = CreateDialogParam(hInstance,
                             MAKEINTRESOURCE(IDD_DIALOG1),
                             0,
                             DlgProc,
                             0);
    if(!hDlg) return (FALSE);
    ShowWindow(hDlg, nCmdShow);
    UpdateWindow(hDlg);
    return (TRUE);
}
void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hwnd, &rect);
    HDC hDc=BeginPaint(hwnd, &ps);
    //call hdc
    EndPaint(hwnd, &ps);
}
