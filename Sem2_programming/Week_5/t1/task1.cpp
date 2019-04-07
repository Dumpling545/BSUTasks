#include "task1.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Word resize";
int fontWidth = 32;
int fontHeight = 48;
const double resizeCoefficient = 1.1;
const TCHAR * text = _T("Dorou");
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

    switch(message){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_KEYDOWN:
            switch(wParam){
                case 187:
                    fontWidth*= resizeCoefficient;
                    fontHeight*=resizeCoefficient;
                    break;
                case 189:
                    fontWidth/=resizeCoefficient;
                    fontHeight/=resizeCoefficient;
                    break;
            }
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case WM_PAINT:
            draw(hwnd);
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
    if(!hWnd) return (FALSE);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return (TRUE);
}
void drawWord(HDC &hdc, RECT wRect){
    HFONT font = CreateFont(fontHeight,fontWidth,60,120,100,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS,PROOF_QUALITY, VARIABLE_PITCH,TEXT("Times New Roman"));
    SelectObject(hdc, font);
    SetBkColor(hdc, RGB(255,255,255));
    SIZE _size;
    GetTextExtentPoint32(hdc, text, _tcslen(text), &_size);
    TextOut(hdc, (wRect.right - _size.cx)/2, (wRect.bottom - _size.cy)/2, text, _tcslen(text));
    //DeleteObject(font);
}
void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hwnd, &rect);
    HDC hdc=BeginPaint(hwnd, &ps);
    drawWord(hdc, rect);
    EndPaint(hwnd, &ps);
}
