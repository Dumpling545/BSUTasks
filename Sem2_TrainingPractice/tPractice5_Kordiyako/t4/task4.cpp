#include "task4.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Grid with circles";
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

    switch(message){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:{
            draw(hwnd);
            break;
        }
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
void drawCircle(HDC &hdc, int x, int y, int radius, COLORREF color){
    HBRUSH brush = CreateSolidBrush(color);
    SelectObject(hdc, brush);
    Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
    DeleteObject(brush);
}
void drawCircles(HDC &hdc,int n, int m, RECT rect){
    int radius = std::min(rect.right/(3*m), rect.bottom/(3*n));
    for(int i = 1; i < n; i++){
        for(int j = 1; j < m; j++){
            drawCircle(hdc, j*rect.right/m, i*rect.bottom/n, radius, RGB(rand()%256, rand()%256, rand()%256));
        }
    }
}

void drawGrid(HDC &hdc,int n, int m, RECT rect){
    if(n > 0 && m > 0){
        int wWidth = rect.right;
        int wHeight = rect.bottom;
        for(int i = 0; i < n+1; i++){
            MoveToEx(hdc, 0, i*wHeight/n, NULL);
            LineTo(hdc, wWidth, i*wHeight/n);
        }
        for(int i = 0; i < m+1; i++){
            MoveToEx(hdc, i*wWidth/m, 0, NULL);
            LineTo(hdc, i*wWidth/m, wHeight);
        }
    }
}
void drawAll(HDC &hdc, RECT rect){
    std::stringstream ss;
    ss << input_str;
    int n, m;
    ss>> n>> m;
    ss.clear();
    drawGrid(hdc, n,m,rect);
    drawCircles(hdc, n,m, rect);
}
void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hwnd, &rect);
    HDC hdc=BeginPaint(hwnd, &ps);
    drawAll(hdc, rect);
    EndPaint(hwnd, &ps);
}
