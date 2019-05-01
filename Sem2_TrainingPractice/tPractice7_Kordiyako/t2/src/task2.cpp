#include "../include/task2.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Diagrams";
const int SIGNATURE_PRECISION = 1;
const int FSIZE_LOWER_BOUND = 8;
const int FSIZE_UPPER_BOUND = 20;
const int DEF_FSIZE = 12;
int red_coef = 1;
int green_coef = 1;
int blue_coef = 1;
int text_size = DEF_FSIZE;
OPENFILENAME file;
std::string fileName = "fishers2018_ANSI.txt";
char szFile[260];
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:{
            draw(hwnd);
            break;
        }
        case WM_COMMAND:
            onCommand(hwnd, wParam);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
INT_PTR CALLBACK DlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_INITDIALOG:
            TCHAR deftext[2];
            _stprintf(deftext, _T("%d"), text_size);
            SetDlgItemText(hdlg, ID_FSIZE, deftext);
            if(red_coef == 1 && green_coef == 1 && blue_coef == 1){
                CheckDlgButton(hdlg, RADIO_FULL, BST_CHECKED);
            } else if(red_coef == 1){
                CheckDlgButton(hdlg, RADIO_RED, BST_CHECKED);
            } else if(green_coef == 1){
                CheckDlgButton(hdlg, RADIO_GREEN, BST_CHECKED);
            } else if(blue_coef == 1){
                CheckDlgButton(hdlg, RADIO_BLUE, BST_CHECKED);
            }
            break;
        case WM_COMMAND:{
            switch(LOWORD(wParam)){
                case IDOK:{
                    TCHAR text[4];
                    GetDlgItemText(hdlg, ID_FSIZE, text, 4);
                    int s = atoi(text);
                    text_size = (
                                (s >= FSIZE_LOWER_BOUND
                                 && s <= FSIZE_UPPER_BOUND)
                                ? s : DEF_FSIZE);
                    if(IsDlgButtonChecked(hdlg, RADIO_RED)){
                        red_coef = 1;
                        green_coef = 0;
                        blue_coef = 0;
                    } else if(IsDlgButtonChecked(hdlg, RADIO_GREEN)){
                        red_coef = 0;
                        green_coef = 1;
                        blue_coef = 0;
                    }else if(IsDlgButtonChecked(hdlg, RADIO_BLUE)){
                        red_coef = 0;
                        green_coef = 0;
                        blue_coef = 1;
                    } else {
                        red_coef = 1;
                        green_coef = 1;
                        blue_coef = 1;
                    }
                    return EndDialog(hdlg, 0);
                    break;
                }
                case IDCANCEL:{
                    return EndDialog(hdlg, 0);
                    break;
                }
            }
            break;
        }
    }
    return FALSE;
}
void onCommand(HWND &hwnd, WPARAM wParam){
    switch(LOWORD(wParam)){
        case IDM_EXIT:
            PostQuitMessage(0);
            break;
        case IDM_ABOUT:
            char  * text;
            text = "Task 2\nTraining practice 7\nAuthor: Yan Kardziyaka ";
            MessageBox(hwnd, _T(text),
                                   "About", MB_OK);
            break;
        case IDM_PROPERTIES:
            DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc);
            break;
        case IDM_OPEN:
            file.lStructSize = sizeof(OPENFILENAME);
            file.lpstrFilter =  _T("Text\0*.txt");
            file.lpstrFile = szFile;
            file.nMaxFile = 256;
            file.lpstrTitle = NULL;
            file.hwndOwner = hwnd;
            file.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
            file.lpstrInitialDir = _T(".\\");
            file.lpstrDefExt = _T("txt");
            if(GetOpenFileName(&file) == TRUE){
                fileName = std::string(file.lpstrFile);
            }
            break;
    }
}

BOOL InitApplication(HINSTANCE hInstance){
    WNDCLASS  wc;
    srand(time(NULL));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.hbrBackground = CreateSolidBrush(RGB(255,255,255));
    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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
void drawDiagrams(HDC &hdc, RECT rect){
    std::ifstream fin(fileName);
    if(FileManager::checkInput(fin)){
        BarChart bar;
        PieChart pie;
        Fisherman f;
        while(fin >> f) {
            pie.addData(f);
            bar.addData(f);
        }
        RECT rect0 = rect;
        rect0.right /= 2;
        RECT rect1 = rect;
        rect1.left = rect0.right;
        pie.draw(hdc, rect1);
        bar.draw(hdc, rect0);
    }
}
void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hwnd, &rect);
    HDC hdc=BeginPaint(hwnd, &ps);
    drawDiagrams(hdc, rect);
    EndPaint(hwnd, &ps);
}

std::string getSignature(std::string lastName, double percentage){
    std::stringstream ss;
    ss.precision(SIGNATURE_PRECISION);
    ss << lastName << ' ' << std::fixed << 100 * percentage << '%';
    return ss.str();
}
