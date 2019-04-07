#pragma once
#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <string>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void drawClockHand(HDC &hdc, int radius, double angle, COLORREF color);
void drawClockHands(HDC &hdc, int radius);
void drawScale(HDC &hdc, int radius);
void drawWatches(HDC &hdc, RECT wRect);
void draw(HWND &hwnd);
