#include "task1.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Car moving";
Car * car;
int timeout = 50;
int t = 0;
POINT curvePoint1;
POINT curvePoint2;
int x_start = 1;
int y_start = 1;
bool paused = false;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_DESTROY:
            KillTimer(hwnd, 0);
            PostQuitMessage(0);
            break;
        case WM_PAINT:{
            draw(hwnd);
            break;
        }
        case WM_CREATE:
            onCreate(hwnd);
            break;
        case WM_TIMER:
            if(!paused) onTimer(hwnd);
            break;
        case WM_RBUTTONDOWN:
            onRButttonDown();
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
void onRButttonDown(){
    if(!paused){
        paused = true;
    } else {
        paused = false;
    }
}
bool temp1 = false;
void onTimer(HWND &hwnd){
    RECT widenedRect;
    GetClientRect(hwnd, &widenedRect);
    t+=timeout;
    curvePoint2 = carCurve(t);
    int dx = curvePoint2.x - curvePoint1.x;
    int dy = curvePoint2.y - curvePoint1.y;
    car->move(((int)car->direction)*dx, dy);
    curvePoint1 = curvePoint2;
    RECT carRect = car->border();
    int carWidth = carRect.right - carRect.left;
    widenedRect.left -=  carWidth;
     widenedRect.right +=  carWidth;
    RECT subtraction;
    SubtractRect(&subtraction, &carRect, &widenedRect);
    if(!IsRectEmpty(&subtraction)){
        car->reverse();
    }
    COLORREF oldColor = car->getItemColor(Car::ItemFlag::CarBody);
    int rvalue = 256*(widenedRect.left - carRect.left)
                    / (1.0*(widenedRect.right - widenedRect.left));
    int gvalue = GetGValue(oldColor);
    int bvalue = 256*(widenedRect.left - carRect.left)
                    / (1.0*(widenedRect.right - widenedRect.left));
    COLORREF newColor = RGB(rvalue, gvalue, bvalue);
    car->setItemColor(Car::ItemFlag::CarBody, newColor);
    InvalidateRect(hwnd, NULL, TRUE);
}
void onCreate(HWND &hwnd){
    RECT rect;
    GetClientRect(hwnd, &rect);
    x_start = rect.right/4;
    curvePoint1.x = x_start;
    y_start = rect.bottom/2;
    curvePoint1.y = y_start;
    SetTimer(hwnd, 0, timeout, NULL);
    COLORREF bodyColor = RGB(rand()%256, rand()%256, rand()%256);
    COLORREF topColor = RGB(rand()%256, rand()%256, rand()%256);
    COLORREF windowColor = RGB(rand()%256, rand()%256, rand()%256);
    COLORREF lightColor = RGB(rand()%256, rand()%256, rand()%256);
    COLORREF wheelColor = RGB(rand()%256, rand()%256, rand()%256);
    car = new Car(x_start, y_start,
                  rect.bottom/4, bodyColor, topColor,
                  windowColor, lightColor, wheelColor);
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
    if(!hWnd) return (FALSE);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return (TRUE);
}
void drawCar(HDC &hdc){
    car->draw(hdc);
}
void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hwnd, &rect);
    HDC hDc=BeginPaint(hwnd, &ps);
    drawCar(hDc);
    EndPaint(hwnd, &ps);
}

POINT carCurve(int t){
    POINT point;
    point.x = x_start + t/10.0;
    point.y = y_start + 100*sin(t/500.0);
    return point;
}
