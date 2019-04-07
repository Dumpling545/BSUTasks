#undef UNICODE
#include <windows.h>
#include <tchar.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "�������� ���� Windows";


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
    MSG msg;
    /*���� �������� hPrevInstance � Win32 ������ ����� NULL���������� ��������� ��� �������� */
    if (!hPrevInstance){
        /* �������������� ���������� -  �������������� ������ ������ ���� � ������������ ��� */
        if (!InitApplication(hInstance)) return (FALSE);
    }
    /* ��������� �������� ����� ���������� -     ������� ������� ���� ���������� */
    if (!InitInstance(hInstance, nCmdShow)) return (FALSE);
    /* ���� ��������� ��������� */
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (msg.wParam);
}


BOOL InitApplication(HINSTANCE hInstance){
    WNDCLASS  wc;
    // ��������� ��������� ������ ���� WNDCLASS
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
    wc.hCursor = LoadCursor(NULL, IDC_APPSTARTING);
    wc.hbrBackground = CreateSolidBrush(RGB(0, 87, 184));
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;
    // ������������ ����� ����
    return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow){
    HWND hWnd;
    hWnd = CreateWindow(
        szClassName,         // ��������� �� ������ ������������������� ����� ������
        szTitle,             // ��������� �� ������ ��������� ����
        WS_OVERLAPPEDWINDOW, // ����� ����
        CW_USEDEFAULT,       // �������������� ���������� ����
        CW_USEDEFAULT,       // ������������ ���������� ����
        CW_USEDEFAULT,       // ������ ����
        CW_USEDEFAULT,       // ������ ����
        NULL,                // ���������� ������������� ����
        NULL,                // ���������� ���� ����
        hInstance,           // ���������� ���������� ����������
        NULL
    );               // ��������� �� �������������� ������ ����
    if(!hWnd) return (FALSE);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return (TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    PAINTSTRUCT ps;
    RECT rect;
    SIZE _size;
    switch(message){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:{
            HDC hDc=BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rect);
            HFONT font = CreateFont(48,36,60,120,700,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS,PROOF_QUALITY, VARIABLE_PITCH,TEXT("Times New Roman"));
            SelectObject(hDc, font);
            SetBkColor(hDc, RGB(0, 87, 184));
            SetTextColor(hDc, RGB(255, 215, 0));
            TCHAR * text = _T("Dorou");
            GetTextExtentPoint32(hDc, text, _tcslen(text), &_size);
            TextOut(hDc, 10, 10, text, _tcslen(text));
            TextOut(hDc, rect.right - _size.cx - 10, 10, text, _tcslen(text));
            TextOut(hDc, 10, rect.bottom - _size.cy - 10, text, _tcslen(text));
            TextOut(hDc, rect.right - _size.cx - 10, rect.bottom - _size.cy - 10, text, _tcslen(text));
            TextOut(hDc, (rect.right - _size.cx)/2, (rect.bottom - _size.cy)/2, text, _tcslen(text));
            EndPaint(hwnd, &ps);
            break;
        }
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
