#include "task1.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Exam";
PhysicalSystem _system;
int timeout = 50;
int t = 0;
bool paused = false;
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
                _system.execute(timeout);
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;
        case WM_KEYDOWN:
            if(wParam == 80){
                if(paused)  paused = false;
                else paused = true;
            }
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
     _system = PhysicalSystem(300, 0, 220, 40, 1.1, 4);
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
