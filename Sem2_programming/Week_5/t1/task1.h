#undef UNICODE
#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <winuser.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void draw(HWND &hwnd);
void drawWord(HDC &hdc, RECT wRect);
