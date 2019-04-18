#pragma once
#include <windows.h>
#include <tchar.h>
#include <sstream>
#include <string>
#include <iostream>
extern LPSTR input_str;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void draw(HWND &hwnd);
void drawSum(HDC &hdc, RECT wRect);
