#pragma once
#include <windows.h>
#include <tchar.h>
#include <sstream>
#include <string>
#include <iostream>
#include <cmath>
extern LPSTR input_str;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void draw(HWND &hwnd);
void drawAll(HDC &hdc, RECT rect);
void drawGrid(HDC &hdc, int n, int m, RECT rect);
void drawCircles(HDC &hdc, int n, int m, RECT rect);
void drawCircle(HDC &hdc, int x, int y, int radius, COLORREF color);
