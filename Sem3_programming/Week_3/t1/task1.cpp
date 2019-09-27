#include "task1.h"
Set<int> set1, set2;
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
    static BaseController * controller = new Controller();
    return controller->handle(hDlg, message, wParam, lParam);
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
