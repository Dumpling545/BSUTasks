#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <cctype>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void draw(HWND &hwnd);
void drawEditBox(HDC &hdc, RECT wRect);
