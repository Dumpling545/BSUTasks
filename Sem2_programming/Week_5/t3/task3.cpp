#include "task3.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Circles";
std::vector<Circle> circles;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

    switch(message){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_ERASEBKGND:
             break;
        case WM_PAINT:{
            draw(hwnd);
            break;
        }
        case WM_LBUTTONDOWN:
            onLeftClick(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            InvalidateRect(hwnd,NULL, TRUE);
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
    if(!hWnd) return (FALSE);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return (TRUE);
}
void onLeftClick(int x, int y){
    int index = -1;
    for(int i = circles.size()-1; i >= 0;i--){
        if(circles[i].isInternal(x,y)){
            index = i;
            break;
        }
    }
    Circle temp;
    if(index == -1){
        temp = Circle(x,y,RGB(rand()%256, rand()%256, rand()%256));
    } else {
        temp = circles[index];
        circles.erase(circles.begin()+index);
        temp.extend();
    }
    circles.push_back(temp);
}
void drawCircles(HDC &hdc){
    for(int i = 0; i < circles.size(); i++){
        circles[i].draw(hdc);
    }
}
void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hwnd, &rect);
    HDC hdc=BeginPaint(hwnd, &ps);
    drawCircles(hdc);
    EndPaint(hwnd, &ps);
}
