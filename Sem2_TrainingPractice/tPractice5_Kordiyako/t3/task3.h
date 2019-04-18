#pragma once
#include <windows.h>
#include <tchar.h>
#include <windowsx.h>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void draw(HWND &hwnd);
void onLeftClick(int x, int y);
void drawPoints(HDC &hdc);
void drawPoint(HDC &hdc, POINT point1, POINT point2);
void endLine();
