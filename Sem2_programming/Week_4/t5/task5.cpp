#include "task5.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Много прямоугольников";
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
    // Заполняем структуру класса окна WNDCLASS
    srand(time(NULL));
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
    // Регистрируем класс окна
    return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow){
    HWND hWnd;
    hWnd = CreateWindow(
        szClassName,         // указатель на строку зарегистрированного имени класса
        szTitle,             // указатель на строку заголовка окна
        WS_OVERLAPPEDWINDOW, // стиль окна
        CW_USEDEFAULT,       // горизонтальная координата окна
        CW_USEDEFAULT,       // вертикальная координата окна
        CW_USEDEFAULT,       // ширина окна
        CW_USEDEFAULT,       // высота окна
        NULL,                // дескриптор родительского окна
        NULL,                // дескриптор меню окна
        hInstance,           // дескриптор экземпляра приложения
        NULL
    );               // указатель на дополнительные данные окна
    if(!hWnd) return (FALSE);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return (TRUE);
}
void drawRects(HDC &hdc, RECT rect, COLORREF startColor, COLORREF endColor, int delta){
    delta = abs(delta);
    int iterations = std::min((rect.bottom - rect.top) / (2*delta), (rect.right - rect.left) / (2*delta));
    int rValue = GetRValue(startColor);
    int gValue = GetGValue(startColor);
    int bValue = GetBValue(startColor);
    int end_rValue = GetRValue(endColor);
    int end_gValue = GetGValue(endColor);
    int end_bValue = GetBValue(endColor);
    int rDelta = (end_rValue - rValue) / iterations;
    int gDelta = (end_gValue - gValue) / iterations;
    int bDelta = (end_bValue - bValue) / iterations;
    for(int i = 0; i < iterations + 1; i++){
        FillRect(hdc, &rect, CreateSolidBrush(RGB(rValue, gValue, bValue)));
        InflateRect(&rect, -delta,-delta);
        rValue+=rDelta;
        gValue+=gDelta;
        bValue+=bDelta;
    }
}
void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    int delta = 6 + rand()%25;
    GetClientRect(hwnd, &rect);
    HDC hDc=BeginPaint(hwnd, &ps);
    drawRects(hDc, rect, RGB(rand()%256, rand()%256, rand()%256),
               RGB(rand()%256, rand()%256, rand()%256),
              delta);
    EndPaint(hwnd, &ps);
}
