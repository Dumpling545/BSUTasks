#include "../include/task2.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Diagrams";
const int SIGNATURE_PRECISION = 2;
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
void drawDiagrams(HDC &hdc, RECT rect){
    std::ifstream fin("fishers2018_ANSI.txt");
    if(FileManager::checkInput(fin)){
        BarChart bar;
        PieChart pie;
        Fisherman f;
        while(fin >> f) {
            pie.addData(f);
            bar.addData(f);
        }
        RECT rect0 = rect;
        rect0.right /= 2;
        RECT rect1 = rect;
        rect1.left = rect0.right;
        pie.draw(hdc, rect1);
        bar.draw(hdc, rect0);
    }
}
void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hwnd, &rect);
    HDC hdc=BeginPaint(hwnd, &ps);
    drawDiagrams(hdc, rect);
    EndPaint(hwnd, &ps);
}

std::string getSignature(std::string lastName, double percentage){
    std::stringstream ss;
    ss.precision(SIGNATURE_PRECISION);
    ss << lastName << ' ' << std::fixed << 100 * percentage << '%';
    return ss.str();
}
