#pragma once
#include "circle.h"
#include <windows.h>
#include <tchar.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <windowsx.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void draw(HWND &hwnd);
void drawCircles(HDC &hdc);
void onLeftClick(int x, int y);
