#include "task6.h"
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Расписание";
Timetable timetable;
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
    wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE-1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;
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

bool isCorrectInputFile(std::ifstream &_fin){
    bool res = true;
    if(!_fin){
        std::cout << "Input file doesn't exist" << std::endl;
        res =  false;
    } else if(_fin.peek() == std::ifstream::traits_type::eof()){
        std::cout << "Input file is empty" << std::endl;
        res = false;
    }
    return res;
}
void readTimetableFromFile(std::string filename){
    std::ifstream fin(filename);
    if(isCorrectInputFile(fin)){
        fin >> timetable;
    }
}
COLORREF chooseLectureColor(char c){
    COLORREF res;
    switch(c){
        case 'л':
            res = RGB(255, 255, 100);
            break;
        case 'п':
            res = RGB(100, 100, 255);
            break;
        case 'н':
            res = RGB(150,150,150);
            break;
        case 'ф':
            res = RGB(100, 255, 100);
            break;
    }
    return res;
}
void drawCellTitles(HDC &hdc, RECT rect, COLORREF bkColor,
                    std::string textTop, std::string textCenter){
    SIZE topSize, centerSize;
    const TCHAR* t_top = _T(textTop.c_str());
    const TCHAR* t_center = _T(textCenter.c_str());
    GetTextExtentPoint32(hdc, t_top, _tcslen(t_top), &topSize);
    GetTextExtentPoint32(hdc, t_center, _tcslen(t_center), &centerSize);
    SetBkColor(hdc, bkColor);
    int topX = rect.left  + (rect.right - rect.left - topSize.cx)/2;
    int topY = rect.top + 5;
    int centerX = rect.left  + (rect.right - rect.left - centerSize.cx)/2;
    int centerY = rect.top + (rect.bottom - rect.top - centerSize.cy)/2;
    TextOut(hdc, topX, topY,  t_top, textTop.size());
    TextOut(hdc, centerX, centerY,  t_center, _tcslen(t_center));
}
void drawCell(HDC &hdc, int rowIndex, int colIndex,
              int cellWidth, int cellHeight,
              int left, int top, COLORREF color,
              std::string textTop, std::string textCenter){
    RECT rect;
    rect.left = left + cellWidth*colIndex;
    rect.top = top + cellHeight*rowIndex;
    rect.right = left + cellWidth*(colIndex+1);
    rect.bottom = top + cellHeight*(rowIndex+1);
    FillRect(hdc, &rect, CreateSolidBrush(color));
    FrameRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));
    SetBkColor(hdc, color);
    drawCellTitles(hdc, rect, color, textTop, textCenter);
}
void drawTimetable(HDC &hdc, Timetable timetable, RECT rect){
    if(!timetable.isEmpty()){
        int rowCount = timetable.days.size();
        int cellHeight = rect.bottom / rowCount;
        int colCount = timetable.getClassesMaxCount() + 1;;
        int cellWidth = rect.right / colCount;
        RECT temp;
        for(int i = 0; i < rowCount; i++){
            drawCell(hdc, i, 0, cellWidth, cellHeight, rect.left, rect.top,
                     RGB(255,255,255), timetable.days[i].name);
            for(int j = 1; j < colCount; j++){
                if(j <= timetable.days[i].classes.size()){
                    drawCell(hdc, i, j, cellWidth, cellHeight, rect.left, rect.top,
                            chooseLectureColor(timetable.days[i].classes[j-1].type),
                             timetable.days[i].classes[j-1].name,
                             timetable.days[i].classes[j-1].lectureHall);
                } else {
                    drawCell(hdc, i, j, cellWidth, cellHeight, rect.left, rect.top,
                        chooseLectureColor('н'));
                }
            }
        }
    }
}
void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hwnd, &rect);
    if(timetable.isEmpty()){
        readTimetableFromFile("input.txt");
    }
    HDC hDc=BeginPaint(hwnd, &ps);
    drawTimetable(hDc, timetable, rect);
    EndPaint(hwnd, &ps);
}
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
