#pragma once
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <cmath>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void drawRects(HDC &hdc, RECT rect, COLORREF startColor, COLORREF endColor, int delta);
void draw(HWND &hwnd);

