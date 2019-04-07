#undef UNICODE
#include <windows.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Создание окна Windows";


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
    MSG msg;
    /*хотя параметр hPrevInstance в Win32 всегда равно NULLпродолжаем проверять его значение */
    if (!hPrevInstance){
        /* инициализируем приложение -  подготавливаем данные класса окна и регистрируем его */
        if (!InitApplication(hInstance)) return (FALSE);
    }
    /* завершаем создание копии приложения -     создаем главное окно приложения */
    if (!InitInstance(hInstance, nCmdShow)) return (FALSE);
    /* Цикл обработки сообщений */
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (msg.wParam);
}


BOOL InitApplication(HINSTANCE hInstance){
    WNDCLASS  wc;
    // Заполняем структуру класса окна WNDCLASS
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    PAINTSTRUCT ps;
    RECT rect;
    switch(message){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:{
            HDC hDc=BeginPaint(hwnd, &ps);
            HBRUSH hbrush = CreateSolidBrush(RGB(0, 87, 184));
            SelectObject(hDc, hbrush);
            GetClientRect(hwnd, &rect);
            Rectangle(hDc, 10, 10, rect.right -10, rect.bottom-10);
            DeleteObject(hbrush);
            hbrush = CreateSolidBrush(RGB(255, 215, 0));
            SelectObject(hDc, hbrush);
            Ellipse(hDc, 10, 10, rect.right -10, rect.bottom-10);
            EndPaint(hwnd, &ps);
            break;
        }
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
