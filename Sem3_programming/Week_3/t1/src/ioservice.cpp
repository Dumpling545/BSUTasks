#include "ioservice.h"
void IOService::sendOutput(HWND hDlg, OutputInfo output){
    for(int i = 0; i < 2; i++){
        SetDlgItemText(hDlg, i + ID_FIRST_EL_VALUE,
                       _T(output.elementInfo[i].view.c_str()));
        SetDlgItemText(hDlg, i + ID_FIRST_EL_TYPE,
                       _T(output.elementInfo[i].type.c_str()));
        SetDlgItemText(hDlg, i + ID_FIRST_EL_FE,
                       _T(output.elementInfo[i].firstElement.c_str()));
        SetDlgItemText(hDlg, i + ID_FIRST_EL_LE,
                       _T(output.elementInfo[i].lastElement.c_str()));
        SetDlgItemText(hDlg, i + ID_FIRST_EL_SUM,
                       _T(output.elementInfo[i].sum.c_str()));
    }
}
InputInfo IOService::unpackRefreshInfo(HWND hDlg){
    InputInfo info;
    info.firstIndex = GetDlgItemInt(hDlg,
                             ID_FIRST_EL_INDEX,
                             NULL,
                             TRUE);
    info.secondIndex = GetDlgItemInt(hDlg,
                             ID_SECOND_EL_INDEX,
                             NULL,
                             TRUE);
    return info;
}
Element* IOService::unpackAddElementInfo(HWND hDlg){
    Element* elem = nullptr;
    int rows, cols;
    TCHAR str[IOService::DEFAULT_TCHAR_ARRAY_LENGTH];
    std::stringstream ss;
    GetDlgItemText(hDlg,
                   ID_FIRST_EL_EDIT,
                   str,
                   IOService::DEFAULT_TCHAR_ARRAY_LENGTH);
    ss << str;
    rows = GetDlgItemInt(hDlg,
                         ID_FIRST_EL_ROWS,
                         NULL,
                         TRUE);
    cols = GetDlgItemInt(hDlg,
                         ID_FIRST_EL_COLS,
                         NULL,
                         TRUE);
    rows = ((rows > 0) ? rows : 1);
    cols = ((cols > 0) ? cols : 1);
    if(rows == 1 || cols == 1){
        rows*=cols;
        double * ar = new double[rows];
        for(int i = 0; i < rows; i++){
            ss >> ar[i];
        }
        elem = new Vector(rows, ar);
    } else {
        double ** td_ar = new double*[rows];
        for(int i = 0; i < rows; i++){
            td_ar[i] = new double[cols];
            for(int j = 0; j < cols; j++){
                ss >>td_ar[i][j];
            }
        }
        elem = new Matrix(rows, cols, td_ar);
    }
    ss.clear();
    return elem;
}
