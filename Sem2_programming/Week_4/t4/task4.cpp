#include "task4.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Геометрические фигуры";
const TCHAR* RECTANGLE = _T("Rectangle");
const TCHAR* ELLIPSE = _T("Ellipse");
const TCHAR* SECTOR = _T("Sector");
const TCHAR* RHOMBUS = _T("Rhombus");
BOOL InitApplication(HINSTANCE hInstance){
    WNDCLASS  wc;
    srand(time(NULL));
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = (WNDPROC)WndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon(NULL, IDI_ASTERISK);
    wc.hCursor          = LoadCursor(NULL, IDC_APPSTARTING);
    wc.hbrBackground    = CreateSolidBrush(RGB(255, 255, 255));
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = szClassName;
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:{
            drawFigures(hwnd);
            break;
        }
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

void deleteObjects(HPEN &hpen, HBRUSH &hbrush){
    DeleteObject(hbrush);
    DeleteObject(hpen);
}

void initValues(const TCHAR* &figure,
                HDC &hDc,
                HPEN &hpen,
                HBRUSH &hbrush,
                TCHAR * &text,
                int &textHeight,
                int &textWidth){
    int psAmount = 5;
    int minwidth = 1;
    int maxdelta = 1;
    hpen = CreatePen(rand() % psAmount, minwidth + rand()%(maxdelta+1),
                     RGB(rand()%256, rand()%256, rand()%256));
    SelectObject(hDc, hpen);
    SIZE _size;
    SetTextColor(hDc, RGB(rand()%256, rand()%256, rand()%256));
    text = _T(const_cast<TCHAR*>(figure));
    GetTextExtentPoint32(hDc, text, _tcslen(text), &_size);
    textHeight = _size.cy;
    textWidth = _size.cx;
    hbrush = CreateSolidBrush(RGB(rand()%256, rand()%256, rand()%256));
    SelectObject(hDc, hbrush);
}

void drawFigure(const TCHAR* &figure,
                HDC &hDc,
                HPEN &hpen,
                HBRUSH &hbrush,
                TCHAR * &text,
                int &textHeight,
                int &textWidth,
                int windowWidth,
                int windowHeight,
                int margin){
    initValues(figure, hDc, hpen, hbrush, text, textHeight, textWidth);
    if(figure == RECTANGLE){
        Rectangle(hDc, margin, margin, windowWidth/2 -  margin,
                       windowHeight/2 - textHeight - 2 * margin);
        TextOut(hDc, 0.25*windowWidth - textWidth/2,
                windowHeight/2 - textHeight - margin, text, _tcslen(text));
    } else if(figure == ELLIPSE){
        Ellipse(hDc, windowWidth/2 + margin, margin, windowWidth - margin,
                       windowHeight/2 - textHeight - 2 * margin);
        TextOut(hDc, 0.75*windowWidth - textWidth/2,
                windowHeight/2 - textHeight - margin, text, _tcslen(text));
    } else if(figure == SECTOR){
        Pie(hDc, margin, windowHeight/2 + margin, windowWidth/2 - margin,
                       windowHeight - textHeight - 2 * margin,
                       windowWidth*0.3 - margin, windowHeight/2 +  margin,
                        margin + windowWidth*0.2, windowHeight/2 + margin);
        TextOut(hDc, 0.25*windowWidth - textWidth/2,
                windowHeight - textHeight - margin, text, _tcslen(text));
    } else if(figure == RHOMBUS){
        POINT points[4];
        points[0] = {0.75*windowWidth, 0.5*windowHeight + margin};
        points[1] = {
            windowWidth - margin,
            (1.5*windowHeight - textHeight - margin)*0.5
        };
        points[2] = {
            0.75*windowWidth,
            windowHeight - textHeight - 2*margin
        };
        points[3] = {
            0.5*windowWidth + margin,
            (1.5*windowHeight - textHeight - margin)*0.5
        };
        Polygon(hDc, points, 4);
        TextOut(hDc, 0.75*windowWidth - textWidth/2,
                windowHeight - textHeight - margin, text, _tcslen(text));
}
    deleteObjects(hpen, hbrush);
}

void drawLine(HDC &hDc, HPEN &hpen, int windowWidth, int windowHeight){
    hpen = CreatePen(PS_SOLID, 2, RGB(rand()%256, rand()%256, rand()%256));
    SelectObject(hDc, hpen);
    MoveToEx(hDc, windowWidth/2, 0, NULL);
    LineTo(hDc, windowWidth/2, windowHeight);
    MoveToEx(hDc, 0, windowHeight/2, NULL);
    LineTo(hDc, windowWidth, windowHeight/2);
    DeleteObject(hpen);
}

void initWindowSize(HWND &hwnd, int &windowWidth, int &windowHeight){
    RECT rect;
    GetClientRect(hwnd, &rect);
    windowWidth = rect.right;
    windowHeight = rect.bottom;
}

void drawFigures(HWND &hwnd){
    PAINTSTRUCT ps;
    HDC hDc = BeginPaint(hwnd, &ps);
    int windowHeight, windowWidth;
    initWindowSize(hwnd, windowWidth, windowHeight);
    HBRUSH hbrush;
    HPEN hpen;
    TCHAR * text;
    int textWidth, textHeight;
    int margin = 10;
    drawLine(hDc, hpen, windowWidth, windowHeight);
    drawFigure(RECTANGLE, hDc, hpen, hbrush, text, textHeight,
               textWidth, windowWidth, windowHeight, margin);
    drawFigure(ELLIPSE, hDc, hpen, hbrush, text, textHeight,
               textWidth, windowWidth, windowHeight, margin);
    drawFigure(SECTOR, hDc, hpen, hbrush, text, textHeight,
               textWidth, windowWidth, windowHeight, margin);
    drawFigure(RHOMBUS, hDc, hpen, hbrush, text, textHeight,
               textWidth, windowWidth, windowHeight, margin);
    EndPaint(hwnd, &ps);
}
