#include "task1.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Exam";
/*parameters to change*/
int N = 3;
double start_angle_rad = 1.1;
int radius = 40;
int thread_length = 120;
int origin_x = 400;
int origin_y = 0;
/*end of changeable parameters*/
PhysicalSystem _system;
int timeout = 50;
int t = 0;
bool paused = false;
INT_PTR CALLBACK DlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_COMMAND:{
            switch(LOWORD(wParam)){
                case IDOK:{
                    TCHAR text[4];
                    GetDlgItemText(hdlg, IDACCEL, text, 4);
                    int a = atoi(text);
                    if(validAcceleration(a)){
                        _system.setAcceleration(a);
                        return EndDialog(hdlg, 0);
                    } else {
                        MessageBox(hdlg, _T("Invalid acceleration"),
                                   "Error", MB_OK);
                    }
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
bool validAcceleration(int a){
    return (a >= 100) && (a <= 999);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_CREATE:
            SetTimer(hwnd, 0, timeout, NULL);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:{
            draw(hwnd);
            break;
        case WM_TIMER:
            if(!paused){
                t+=timeout;
                _system.execute(t);
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;
        case WM_KEYDOWN:
            switch(wParam){
                case 80:{
                    if(paused)  paused = false;
                    else paused = true;
                    break;
                }
                case 114:
                    DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc);
                    break;
            }
            if(wParam == 80)
            break;
        }
        case WM_LBUTTONDOWN:
            _system.setColor(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
BOOL InitApplication(HINSTANCE hInstance){
    WNDCLASS  wc;
    srand(time(NULL));
     _system = PhysicalSystem(origin_x, origin_y, thread_length,
                              radius, start_angle_rad, N);
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
void drawSystem(HDC &hdc, RECT rect){
    _system.draw(hdc);
}
void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hwnd, &rect);
    HDC hDc=BeginPaint(hwnd, &ps);
    drawSystem(hDc, rect);
    EndPaint(hwnd, &ps);
}
