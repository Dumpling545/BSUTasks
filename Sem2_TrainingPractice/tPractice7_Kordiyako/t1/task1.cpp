#include "task1.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Car moving";
Car * car;
int timeout = 50;
int t = 0;
POINT curvePoint1;
POINT curvePoint2;
int sign = 1;
int x_start = 1;
int y_start = 1;
bool paused = false;
COLORREF stdColor = RGB(100,100,100);
static COLORREF acrCustClr[16];
static CHOOSECOLOR ccs;
INT_PTR CALLBACK DlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_COMMAND:{
            switch(LOWORD(wParam)){
                case IDOK:{
                    TCHAR text[4];
                    GetDlgItemText(hdlg, IDC_HEIGHT, text, 4);
                    int newHeight = atoi(text);
                    car->setHeight(newHeight);
                    return EndDialog(hdlg, 0);
                    break;
                }
                case IDCANCEL:{
                    return EndDialog(hdlg, 0);
                    break;
                }
                case IDC_COLOR:
                    {
                        ccs.lStructSize = sizeof(CHOOSECOLOR);
                        ccs.hwndOwner = hdlg;
                        ccs.rgbResult = stdColor;
                        ccs.Flags = CC_RGBINIT | CC_FULLOPEN;
                        ccs.lpCustColors = (LPDWORD)acrCustClr;
                        if(ChooseColor(&ccs)){
                            stdColor = ccs.rgbResult;
                            car->setItemColor(Car::ItemFlag::CarTop, stdColor);
                        }
                    break;
                    }
            }
            break;
        }
    }
    return FALSE;
}
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
        case WM_COMMAND:
            onCommand(hwnd, wParam);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
void onCommand(HWND &hwnd, WPARAM wParam){
    switch(LOWORD(wParam)){
        case IDM_START:
            paused = false;
            break;
        case IDM_STOP:
            paused = true;
            break;
        case IDM_EXIT:
            PostQuitMessage(0);
            break;
        case IDM_PROP:
            DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc);
            break;
    }
}
void onRButttonDown(){
    if(!paused){
        paused = true;
    } else {
        paused = false;
    }
}
void onTimer(HWND &hwnd){
    RECT rect;
    GetClientRect(hwnd, &rect);
    t+=timeout;
    curvePoint2 = carCurve(t);
    int dx = curvePoint2.x - curvePoint1.x;
    int dy = curvePoint2.y - curvePoint1.y;
    car->move(sign*dx, dy);
    curvePoint1 = curvePoint2;
    RECT carRect = car->border();
    RECT subtraction;
    SubtractRect(&subtraction, &carRect, &rect);
    if(!IsRectEmpty(&subtraction)){
        sign*=-1;
    }
    COLORREF oldColor = car->getItemColor(Car::ItemFlag::CarBody);
    int rvalue = 256*(rect.left - carRect.left)/(1.0*(rect.right - rect.left));
    int gvalue = GetGValue(oldColor);
    int bvalue = 256*(rect.left - carRect.left)/(1.0*(rect.right - rect.left));
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
