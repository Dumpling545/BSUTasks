#include "task2.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Watches";
long seconds = 0;
bool paused = false;
const int ID_TIMER = 1;
const double PI = 3.14159265359;
const int millisInSecond = 100;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_DESTROY:
            KillTimer(hwnd, ID_TIMER);
            PostQuitMessage(0);
            break;
        case WM_PAINT:{
            draw(hwnd);
            break;
        }
        case WM_KEYDOWN:
            switch(wParam){
                case 189:
                    paused = true;
                    break;
                case 187:
                    paused = false;
                    break;
                case 83:
                    if(GetKeyState(VK_CONTROL) < 0){
                        seconds = 0;
                        KillTimer(hwnd, ID_TIMER);
                        SetTimer(hwnd, ID_TIMER, millisInSecond, (TIMERPROC) NULL);
                        InvalidateRect(hwnd, NULL, true);
                    }
                    break;
            }
            break;
        case WM_TIMER:
            if(!paused){
                seconds++;
            }
            InvalidateRect(hwnd, NULL, true);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
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
    SetTimer(hWnd, ID_TIMER, millisInSecond, (TIMERPROC) NULL);
    if(!hWnd) return (FALSE);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return (TRUE);
}
void drawClockHand(HDC &hdc, int radius, double angle, COLORREF color){
    HPEN pen = CreatePen(PS_SOLID, 1, color);
    SelectObject(hdc, pen);
    int endX = cos(angle)*radius;
    int endY = sin(angle)*radius;
    MoveToEx(hdc,0, 0, NULL);
    LineTo(hdc,endX, endY);
    DeleteObject(pen);
}
void drawClockHands(HDC &hdc, int radius){
    int cur_seconds = seconds % 60;
    int cur_minutes = (seconds / 60) % 60;
    int cur_hours = (seconds / 3600) % 24;
    drawClockHand(hdc, radius*0.9, cur_seconds*2*PI/60 - PI/2, RGB(0,0,255));
    drawClockHand(hdc, radius*0.7, cur_minutes*2*PI/60 - PI/2, RGB(255,0,0));
    drawClockHand(hdc, radius*0.4, cur_hours*2*PI/24 - PI/2, RGB(0,255,0));
}
void drawScale(HDC &hdc, int radius){
    int scaleCount = 60;
    double clockhandSize = 0.9;
    for(int i = 0; i < scaleCount; i++){
        double angle = i*2*PI/scaleCount;
        int endX = cos(angle)*radius;
        int endY = sin(angle)*radius;
        int startX = endX*clockhandSize;
        int startY = endY*clockhandSize;
        MoveToEx(hdc,startX, startY, NULL);
        LineTo(hdc,endX, endY);
    }
}
void drawWatches(HDC &hdc, RECT wRect){
    int margin = 10;
    int wWidth = wRect.right - wRect.left;
    int wHeight = wRect.bottom - wRect.top;
    int diameter = std::min(wHeight, wWidth) - 2*margin;
    int left = (wWidth - diameter)/2 ;
    int top =  (wHeight - diameter)/2;
    Ellipse(hdc, left, top, left + diameter, top + diameter);
    SetViewportOrgEx(hdc, left +diameter/2,  top + diameter/2, NULL);
    drawScale(hdc, diameter/2);
    drawClockHands(hdc, diameter/2);
}
void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hwnd, &rect);
    HDC hdc=BeginPaint(hwnd, &ps);
    drawWatches(hdc, rect);
    EndPaint(hwnd, &ps);
}
