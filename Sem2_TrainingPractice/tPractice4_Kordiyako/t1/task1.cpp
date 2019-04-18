#include "task1.h"
struct GraphPoint{
    double g_x;
    double g_y;
};
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Function graph";

bool isMouseLButtonPressed = false;
POINT startSelection, endSelection;
POINT mousePosition;
/*(G_START_x, G_START_Y),(G_END_X, G_END_Y) -
        graph points that define rect of function graph that will be drawn */
double G_START_X = -5;
double G_START_Y = -10;
double G_END_X = 5;
double G_END_Y = 10;
/* graphDecimalPrecision
        precision of numbers that will be drawn
        under axes on the function graph */
int graphDecimalPrecision = 2;
/* amountOfScalesByAxe
        how many scales will be drawn on EACH axe */
int amountOfScalesByAxe = 11;
/* scaleSize
        length of each scale (in px) */
int scaleSize = 4;
/* margin
        if X-axe or Y-axe after resizing will be closer than margin (in px)
        to the edge of window, THIS axe will be moved automatically to the right
        edge (for Y-axe) / top edge (for X-axe) */
int margin = 15;
/* minSelectionSize
        if selected area height OR width is less than minSelectionSize (in px),
        graph resizing won't happen */
int minSelectionSize = 10;
/* func
        function to be drawn on graph with
        (possible, not required) parameters _a, _b, _c */
int _a = 1;
int _b = 1;
int _c = 1;
std::function<double(double)> func = [](double g_x) ->
                            double{return _a * g_x * (g_x) + _b * g_x + _c;};

/* functionColor
        color of function graph */
COLORREF functionColor = RGB(255, 0, 0);
/* pointerToAxesColor
        color of lines which shows graph coordinates of mouse */
COLORREF pointerToAxesColor = RGB(0, 255, 0);
/* pointColor
        color of point (g_x, function(g_x)),
        where g_x - graph coordinate of mouse  */
COLORREF pointColor = RGB(0,0,255);

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

    switch(message){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:{
            draw(hwnd);
            break;
        }
        case WM_MOUSEMOVE:
                onMouseMove(hwnd, lParam);
            break;
        case WM_LBUTTONDOWN:
                onLButtonDown(hwnd, lParam);
            break;
        case WM_LBUTTONUP:
                onLButtonUp(hwnd, lParam);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

BOOL InitApplication(HINSTANCE hInstance){
    WNDCLASS  wc;
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

    std::stringstream ss;
    ss << input_str;
    ss>> G_START_X >> G_END_X>>_a>> _b >> _c;
    ss.clear();

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

void fillWithCoordinate(std::string &s, double coor){
    s.clear();
    s = std::to_string(coor);
    s.erase(s.find('.') + graphDecimalPrecision + 1,
    std::string::npos);
}

void resizeAxes(RECT rect){
    if(endSelection.x < startSelection.x) {
        int temp = endSelection.x;
        endSelection.x = startSelection.x;
        startSelection.x = temp;
    }
    if(endSelection.y > startSelection.y) {
        int temp = endSelection.y;
        endSelection.y = startSelection.y;
        startSelection.y = temp;
    }
    GraphPoint _start, _end;
    _start = pointToGraphpoint(startSelection.x, startSelection.y, rect);
    _end = pointToGraphpoint(endSelection.x, endSelection.y, rect);
    G_START_X   = _start.g_x;
    G_START_Y   = _start.g_y;
    G_END_X     = _end.g_x;
    G_END_Y     = _end.g_y;
}

void onLButtonDown(HWND &hwnd, LPARAM lParam){
    isMouseLButtonPressed = true;
    startSelection.x = GET_X_LPARAM(lParam);
    startSelection.y = GET_Y_LPARAM(lParam);
}

void onLButtonUp(HWND &hwnd, LPARAM lParam){
    if(isMouseLButtonPressed){
        RECT rect;
        GetClientRect(hwnd, &rect);
        endSelection.x = GET_X_LPARAM(lParam);
        endSelection.y = GET_Y_LPARAM(lParam);
        if(abs(endSelection.x - startSelection.x) >= minSelectionSize
           && abs(endSelection.y - startSelection.y) >= minSelectionSize){
            resizeAxes(rect);
        }
        isMouseLButtonPressed = false;
        InvalidateRect(hwnd, NULL, TRUE);
    }
}

void onMouseMove(HWND &hwnd, LPARAM lParam){
    mousePosition.x = GET_X_LPARAM(lParam);
    mousePosition.y = GET_Y_LPARAM(lParam);
    InvalidateRect(hwnd, NULL, TRUE);
}

POINT getOriginAtWindow(RECT rect){
    POINT origin = graphpointToPoint(0, 0, rect);
    if(origin.y < margin || origin.y > rect.bottom - margin){
        origin.y = scaleSize;
    }
    if(origin.x < margin || origin.x > rect.right - margin){
        origin.x = scaleSize;
    }
    return origin;
}

POINT graphpointToPoint(double g_x, double g_y, RECT rect){
    POINT point;
    point.x = (rect.right / (G_END_X - G_START_X))*(g_x - G_START_X);
    point.y = (rect.bottom / (G_END_Y - G_START_Y))*(G_END_Y - g_y);
    return point;
}

GraphPoint pointToGraphpoint(int x, int y, RECT rect){
    GraphPoint graphpoint;
    graphpoint.g_x = G_START_X +
                        ((G_END_X - G_START_X) / ((double)rect.right))*x;
    graphpoint.g_y = G_END_Y -
                        ((G_END_Y - G_START_Y) / ((double)rect.bottom))*y;
    return graphpoint;
}

void drawRect(HDC &hdc){
    Rectangle(hdc, startSelection.x, startSelection.y,
              mousePosition.x, mousePosition.y);
}

void drawAxes(HDC &hdc, RECT rect, POINT origin){
    MoveToEx(hdc, 0, origin.y, NULL);
    LineTo(hdc, rect.right, origin.y);
    MoveToEx(hdc,origin.x, 0, NULL);
    LineTo(hdc, origin.x, rect.bottom);
}

void drawScalesOfAxes(HDC &hdc, RECT rect, POINT origin){
    double g_valueOfDivision_x = (G_END_X - G_START_X) /
                                    ((double)amountOfScalesByAxe + 1);
    double g_valueOfDivision_y = (G_END_Y - G_START_Y) /
                                    ((double)amountOfScalesByAxe + 1);
    double g_axe_x = G_START_X + g_valueOfDivision_x;
    double g_axe_y = G_START_Y + g_valueOfDivision_y;
    POINT temp;
    std::string text;
    for(int i = 0; i < amountOfScalesByAxe; i++){
        temp = graphpointToPoint(g_axe_x, g_axe_y, rect);
        MoveToEx(hdc, temp.x, origin.y - scaleSize, NULL);
        LineTo(hdc, temp.x, origin.y + scaleSize);
        fillWithCoordinate(text, g_axe_x);
        TextOut(hdc, temp.x - scaleSize, origin.y + 2 * scaleSize,
                _T(text.c_str()), text.size());
        g_axe_x += g_valueOfDivision_x;
        MoveToEx(hdc, origin.x - scaleSize, temp.y, NULL);
        LineTo(hdc, origin.x + scaleSize, temp.y);
        fillWithCoordinate(text, g_axe_y);
        TextOut(hdc, origin.x + 2 * scaleSize, temp.y - scaleSize,
                _T(text.c_str()), text.size());
        g_axe_y += g_valueOfDivision_y;
    }
}

void drawPointerToAxes(HDC &hdc, RECT rect, POINT origin){
    HPEN pen = CreatePen(PS_SOLID, 1, pointerToAxesColor);
    SelectObject(hdc, pen);
    MoveToEx(hdc, mousePosition.x, origin.y, NULL);
    LineTo(hdc, mousePosition.x, mousePosition.y);
    MoveToEx(hdc,origin.x, mousePosition.y, NULL);
    LineTo(hdc, mousePosition.x, mousePosition.y);
    DeleteObject(pen);
}

void drawFunction(HDC &hdc, RECT rect){
    for(int x = 1; x < rect.right; x++){
        GraphPoint graphpoint = pointToGraphpoint(x, 0, rect);
        POINT point = graphpointToPoint(0, func(graphpoint.g_x), rect);
        SetPixel(hdc, x, point.y, functionColor);
    }
}

void drawPointAtGraph(HDC &hdc, RECT rect, POINT origin){
    GraphPoint graphpoint = pointToGraphpoint(mousePosition.x,
                                              mousePosition.y,
                                              rect);
    graphpoint.g_y = func(graphpoint.g_x);
    POINT windowPoint = graphpointToPoint(graphpoint.g_x,
                                          graphpoint.g_y,
                                          rect);
    HPEN pen = CreatePen(PS_SOLID, 5, pointColor);
    SelectObject(hdc, pen);
    Rectangle(hdc, windowPoint.x - 2,  windowPoint.y - 2,
              windowPoint.x + 2, windowPoint.y + 2);
    std::string coor1, coor2;
    fillWithCoordinate(coor1, graphpoint.g_x);
    fillWithCoordinate(coor2, graphpoint.g_y);
    std::string result = "(" + coor1 + ", " + coor2 + ")";
    SetTextColor(hdc, pointColor);
    TextOut(hdc, windowPoint.x + 2, windowPoint.y + 2,
            _T(result.c_str()), result.size());
    DeleteObject(pen);
}

void drawFunctionGraph(HDC &hdc, RECT rect){
    if(isMouseLButtonPressed){
        drawRect(hdc);
    }
    POINT origin = getOriginAtWindow(rect);
    drawAxes(hdc, rect, origin);
    drawScalesOfAxes(hdc, rect, origin);
    drawPointerToAxes(hdc, rect, origin);
    drawFunction(hdc, rect);
    drawPointAtGraph(hdc, rect, origin);
}

void draw(HWND &hwnd){
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hwnd, &rect);
    HDC hdc=BeginPaint(hwnd, &ps);
    drawFunctionGraph(hdc, rect);
    EndPaint(hwnd, &ps);
}
