#include "task1.h"
Set<int> set1, set2;
const int DEFAULT_TCHAR_ARRAY_LENGTH = 100;
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_COMMAND:
            switch(LOWORD(wParam)){
                case ID_REFRESH:
                    TCHAR str[DEFAULT_TCHAR_ARRAY_LENGTH];
                    std::stringstream ss;
                    GetDlgItemText(hDlg,
                                   ID_FIRST_SET_EDIT,
                                   str,
                                   DEFAULT_TCHAR_ARRAY_LENGTH);
                    ss << str;
                    ss >> set1;
                    ss.clear();
                    ss << set1;
                    ss.getline(str, DEFAULT_TCHAR_ARRAY_LENGTH);
                    SetDlgItemText(hDlg, ID_FIRST_SET_VIEW, str);
                    ss.clear();

                    GetDlgItemText(hDlg,
                                   ID_SECOND_SET_EDIT,
                                   str,
                                   DEFAULT_TCHAR_ARRAY_LENGTH);
                    ss << str;
                    ss >> set2;
                    ss.clear();
                    ss << set2;
                    ss.getline(str, DEFAULT_TCHAR_ARRAY_LENGTH);
                    SetDlgItemText(hDlg, ID_SECOND_SET_VIEW, str);

                    ss.clear();
                    ss << set1 + set2;
                    ss.getline(str, DEFAULT_TCHAR_ARRAY_LENGTH);
                    SetDlgItemText(hDlg, ID_UNION_VIEW, str);

                    ss.clear();
                    ss << set1 - set2;
                    ss.getline(str, DEFAULT_TCHAR_ARRAY_LENGTH);
                    SetDlgItemText(hDlg, ID_DIFFERENCE_VIEW, str);

                    ss.clear();
                    ss << set1 * set2;
                    ss.getline(str, DEFAULT_TCHAR_ARRAY_LENGTH);
                    SetDlgItemText(hDlg, ID_INTERSECTION_VIEW, str);
                    std::string std_str = ((set1 == set2) ? "Yes" : "No");
                    SetDlgItemText(hDlg, ID_EQUAL_STATE_VIEW, _T(std_str.c_str()));
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
