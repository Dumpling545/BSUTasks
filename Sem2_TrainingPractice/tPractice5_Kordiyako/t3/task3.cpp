#include "task3.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Title";
std::vector<POINT> points;
bool isPressed = false;
int ID_TIMER = 1;
int delay = 10;
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
        case WM_TIMER:
            if(!points.empty()){
                points.erase(points.begin());
                InvalidateRect(hwnd,NULL, TRUE);
            }
            break;
        case WM_LBUTTONDOWN:
            isPressed = true;
            break;
        case WM_LBUTTONUP:
            isPressed = false;
            endLine();
            break;
        case WM_MOUSEMOVE:
            if(isPressed){
                onLeftClick(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                InvalidateRect(hwnd,NULL, TRUE);
            }
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
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
    SetTimer(hWnd, ID_TIMER, delay, (TIMERPROC) NULL);
    if(!hWnd) return (FALSE);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return (TRUE);
}
void drawLine(HDC &hdc, POINT point1, POINT point2){
    if(point1.x * point2.x > 0 &&  point1.y * point2.y > 0){
        MoveToEx(hdc, point1.x, point1.y, NULL);
        LineTo(hdc, point2.x, point2.y);
    }
    //SetPixel(hdc, point.x, point.y, RGB(0, 0, 0));
}
void drawLines(HDC &hdc){
    int length = points.size();
    for(int i = 0;i < length-1; i++){
        drawLine(hdc, points[i], points[i+1]);
    }
}
void onLeftClick(int x, int y){
    POINT point;
    point.x = x;
    point.y = y;
    points.push_back(point);
}
void endLine(){
    POINT point;
    point.x = -1;
    point.y = -1;
    points.push_back(point);
}
void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hwnd, &rect);
    HDC hDc=BeginPaint(hwnd, &ps);
    drawLines(hDc);
    EndPaint(hwnd, &ps);
}
