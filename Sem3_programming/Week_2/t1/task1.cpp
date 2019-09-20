#include "task1.h"
Set<int> set1, set2;
const int DEFAULT_TCHAR_ARRAY_LENGTH = 200;
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_COMMAND:
            switch(LOWORD(wParam)){
                case ID_REFRESH:
                    refresh(hDlg);
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
void refresh(HWND hDlg){
    Element* elems[2] = {nullptr, nullptr};
    int rows, cols;
    TCHAR str[DEFAULT_TCHAR_ARRAY_LENGTH];
    std::stringstream ss;
    for(int index = 0; index < 2; index++){
        GetDlgItemText(hDlg,
                       index + ID_FIRST_EL_EDIT,
                       str,
                       DEFAULT_TCHAR_ARRAY_LENGTH);
        ss << str;
        rows = GetDlgItemInt(hDlg, index + ID_FIRST_EL_ROWS, NULL, TRUE);
        cols = GetDlgItemInt(hDlg, index + ID_FIRST_EL_COLS, NULL, TRUE);
        rows = ((rows > 0) ? rows : 1);
        cols = ((cols > 0) ? cols : 1);
        if(rows == 1 || cols == 1){
            rows*=cols;
            double * ar = new double[rows];
            for(int i = 0; i < rows; i++){
                ss >> ar[i];
            }
            elems[index] = new Vector(rows, ar);
        } else {
            double ** td_ar = new double*[rows];
            for(int i = 0; i < rows; i++){
                td_ar[i] = new double[cols];
                for(int j = 0; j < cols; j++){
                    ss >>td_ar[i][j];
                }
            }
            elems[index] = new Matrix(rows, cols, td_ar);
        }
        ss.clear();
    }
    Set<Element*> set = {elems[0], elems[1]};
    SetIterator<Element*> it = set.iterator();
    int index = 0;
    do{
        //value
        ToString to_str_visitor;
        it.current()->accept(to_str_visitor);
        SetDlgItemText(hDlg, index + ID_FIRST_EL_VALUE,
                       _T(to_str_visitor.value.c_str()));
        //type
        GetType g_type_visitor;
        it.current()->accept(g_type_visitor);
        SetDlgItemText(hDlg, index + ID_FIRST_EL_TYPE,
                       _T(g_type_visitor.value.c_str()));
        //first element
        ss.str("");
        FirstElement fe_visitor;
        it.current()->accept(fe_visitor);
        ss << fe_visitor.value;
        SetDlgItemText(hDlg, index + ID_FIRST_EL_FE, _T(ss.str().c_str()));
        //last element
        ss.str("");
        LastElement le_visitor;
        it.current()->accept(le_visitor);
        ss << le_visitor.value;
        SetDlgItemText(hDlg, index + ID_FIRST_EL_LE, _T(ss.str().c_str()));
        //sum
        ss.str("");
        SumOfElements sum_visitor;
        it.current()->accept(sum_visitor);
        ss << sum_visitor.value;
        SetDlgItemText(hDlg, index + ID_FIRST_EL_SUM, _T(ss.str().c_str()));
        ++index;
        it.next();
    } while(it.hasNext());
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
