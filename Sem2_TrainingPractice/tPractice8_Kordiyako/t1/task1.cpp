#include "task1.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Poll";
OPENFILENAME file;
char szFile[260];
int current_id = 0;
int radio_ids[] = {IDRADIO_1, IDRADIO_2, IDRADIO_3, IDRADIO_4, IDRADIO_5};
int check_ids[]= {IDCHECK_1, IDCHECK_2, IDCHECK_3, IDCHECK_4, IDCHECK_5};
Poll poll;
AnswerForm answerForm;
INT_PTR CALLBACK DlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_INITDIALOG:{
            initDialog(hdlg);
            break;
        }
        case WM_COMMAND:{
            switch(LOWORD(wParam)){
                case IDNEXTBUTTON:{
                    addAnswers(hdlg);
                    return nextQuestionDialogBox(hdlg);
                    break;
                }
                case IDPREVBUTTON:{
                    addAnswers(hdlg);
                    return prevQuestionDialogBox(hdlg);
                    break;
                }
                case IDENDBUTTON:{
                    addAnswers(hdlg);
                    HWND prnt = GetParent(hdlg);
                    INT_PTR res = EndDialog(hdlg, 0);
                    finalMessageBox(prnt);
                    return res;
                    break;
                }
            }
            break;
        }
    }
    return FALSE;
}
void initDialog(HWND &hdlg){
    SetDlgItemText(hdlg, IDQUESTION,
                            _T(poll.questions[current_id].text.c_str()));
    bool isRadio = (poll.questions[current_id].type ==
                    QuestionType::OneAnswer);
    int * ids = (isRadio) ? radio_ids : check_ids;
    for(int i = 0; i < 5; i++){
        if(i < poll.questions[current_id].answers.size()){
            SetDlgItemText(hdlg, ids[i],
                _T(
                    poll.questions[current_id].answers[i].statement.c_str()
                    ));
            CheckDlgButton(hdlg, ids[i],
                           answerForm.getCheckState(current_id, i));
        } else {
            ShowWindow(GetDlgItem(hdlg, ids[i]), SW_HIDE);
        }
    }
    if(current_id == 0){
        EnableWindow(GetDlgItem(hdlg, IDPREVBUTTON), FALSE);
    } else if(current_id == poll.questions.size()-1){
        EnableWindow(GetDlgItem(hdlg, IDNEXTBUTTON), FALSE);
    }
}
INT_PTR nextQuestionDialogBox(HWND& hdlgCurrent){
    INT_PTR result = FALSE;
    if(current_id == 0){
        EnableWindow(GetDlgItem(hdlgCurrent, IDPREVBUTTON), TRUE);
    }
    current_id++;
    if(current_id < poll.questions.size()){
        result = questionDialogBox(hdlgCurrent);
    }
    return result;
}
INT_PTR prevQuestionDialogBox(HWND& hdlgCurrent){
    INT_PTR result = FALSE;
    if(current_id == poll.questions.size()-1){
        EnableWindow(GetDlgItem(hdlgCurrent, IDNEXTBUTTON), TRUE);
    }
    current_id--;
    if(current_id >= 0){
        result = questionDialogBox(hdlgCurrent);
    }
    return result;
}
INT_PTR questionDialogBox(HWND& hdlgCurrent){
    INT_PTR res = EndDialog(hdlgCurrent, 0);
    if(poll.questions[current_id].type ==
       QuestionType::OneAnswer){
        DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG1),
                  GetParent(hdlgCurrent),DlgProc);
    } else {
        DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG2),
                  GetParent(hdlgCurrent),DlgProc);
    }
    return res;
}
void addAnswers(HWND& hdlg){
    bool isRadio = (poll.questions[current_id].type ==
                            QuestionType::OneAnswer);
    int * ids = (isRadio) ? radio_ids : check_ids;
    for(int j = 0; j < poll.questions[current_id].answers.size(); j++){
        answerForm.addAnswer(current_id, j,
                             IsDlgButtonChecked(hdlg, ids[j]));
    }
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:{
            draw(hwnd);
            break;
        }
        case WM_LBUTTONDOWN:
            onLButtonDown(hwnd, wParam, lParam);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
void onLButtonDown(HWND &hwnd, WPARAM wParam, LPARAM lParam){
    file.lStructSize = sizeof(OPENFILENAME);
    file.lpstrFilter =  _T("Text\0*.txt");
    file.lpstrFile = szFile;
    file.nMaxFile = 256;
    file.lpstrTitle = NULL;
    file.hwndOwner = hwnd;
    file.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
    file.lpstrInitialDir = _T(".\\");
    file.lpstrDefExt = _T("txt");
    if(GetOpenFileName(&file) == TRUE &&
       PollFactory::InitPoll(poll, std::string(file.lpstrFile))){
        answerForm = AnswerForm(poll.questions.size());
        current_id = 0;
        if(poll.questions[current_id].type == QuestionType::OneAnswer){
            DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG1), hwnd,DlgProc);
        } else {
            DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG2), hwnd,DlgProc);
        }
    } else {
        MessageBox(hwnd,
                   _T("Invalid file!"),
                   _T("Error"),
                   MB_OK | MB_ICONERROR);
        SendMessage(hwnd, WM_LBUTTONDOWN, wParam, lParam);
    }
}
void writeAnswersInStream(std::ostream & out, std::string res){
    out << "Poll header: " << poll.header << "\n";
    out << "Poll result: " << res << "\n\n";
    for(int i = 0; i < poll.questions.size(); i++){
        out << "Question #" << (i + 1) << ": " << poll.questions[i].text <<'\n';
        out << "Answer:";
        for(int j = 0; j < poll.questions[i].answers.size(); j++){
            if(answerForm.getCheckState(i, j)){
                out << "   " << poll.questions[i].answers[j].statement;
            }
        }
        out << "\n\n";
    }
}
BOOL InitApplication(HINSTANCE hInstance){
    WNDCLASS  wc;
    //srand(time(NULL));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE-1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;
    return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow){
    HWND hWnd;
    hWnd = CreateWindow(
        szClassName,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    if(!hWnd) return (FALSE);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return (TRUE);
}
void finalMessageBox(HWND &hwnd){
    std::string res = std::to_string((int)answerForm.getResult(poll)) + "%";
    std::string text = "Poll ended. Your result is "
    + res + ". " +
    "Do you want to save your result as text file?";
    int msgboxID = MessageBox(hwnd,
               _T(text.c_str()),
               _T("Poll result"),
               MB_YESNO | MB_ICONINFORMATION);
    switch (msgboxID){
        case IDYES:
            file.lpstrTitle = _T("Открыть файл для записи");
            file.Flags = OFN_NOTESTFILECREATE;
            if(GetSaveFileName(&file)){
                std::ofstream fout;
                fout.open(szFile);
                writeAnswersInStream(fout, res);
                fout.close();
            } else {
                MessageBox(hwnd,
                _T("Error while saving your results"),
                _T("Error"),
                MB_OK | MB_ICONERROR);
            }
            break;
    }
}
void drawText(HDC &hdc, RECT wRect){
    TCHAR * text;
    text = _T("Tap anywhere to load poll");
    SIZE tSize;
    GetTextExtentPoint32(hdc, text, _tcslen(text), &tSize);
    int wWidth = wRect.right - wRect.left;
    int wHeight = wRect.bottom - wRect.top;
    int t_x = (wWidth - tSize.cx) / 2;
    int t_y = (wHeight - tSize.cy) / 2;
    TextOut(hdc, t_x, t_y, text, _tcslen(text));
}
void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hwnd, &rect);
    HDC hDc=BeginPaint(hwnd, &ps);
    drawText(hDc, rect);
    EndPaint(hwnd, &ps);
}
