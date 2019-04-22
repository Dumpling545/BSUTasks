#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <windowsx.h>
#include "include/physicalsystem.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void draw(HWND &hwnd);
void drawSystem(HDC &hdc, RECT rect);
