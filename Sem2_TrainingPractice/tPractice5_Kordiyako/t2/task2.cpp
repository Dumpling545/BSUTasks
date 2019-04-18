#include "task2.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "EditBox Simulation";
std::string text;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

    switch(message){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:{
            draw(hwnd);
            break;
        }
        case WM_CHAR:{
            char c = (char) wParam;
            if(std::isprint(c) && text.size() < text.max_size()){
                text+=c;
            } else if(wParam == '\b'/*0x08*/ && text.size() > 0){
                text.pop_back();
            }
            InvalidateRect(hwnd, NULL, TRUE);
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
void drawEditBox(HDC &hdc, RECT wRect){
    SIZE _size;
    GetTextExtentPoint32(hdc, _T(text.c_str()), text.size(), &_size);
    TextOut(hdc, (wRect.right - _size.cx)/2, (wRect.bottom - _size.cy)/2, _T(text.c_str()), text.size());
}
void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hwnd, &rect);
    HDC hdc=BeginPaint(hwnd, &ps);
    drawEditBox(hdc, rect);
    EndPaint(hwnd, &ps);
}
