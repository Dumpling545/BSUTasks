#pragma once
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <tchar.h>
#include <string>
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void deleteObjects(HPEN &hpen, HBRUSH &hbrush);
void initValues(const TCHAR* &figure,
                HDC &hDc,
                HPEN &hpen,
                HBRUSH &hbrush,
                TCHAR * &text,
                int &textHeight,
                int &textWidth);
void drawFigure(const TCHAR* &figure,
                HDC &hDc,
                HPEN &hpen,
                HBRUSH &hbrush,
                TCHAR * &text,
                int &textHeight,
                int &textWidth,
                int windowWidth,
                int windowHeight,
                int margin);
void drawLine(HDC &hDc, HPEN &hpen, int windowWidth, int windowHeight);
void initWindowSize(HWND &hwnd, int &windowWidth, int &windowHeight);
void drawFigures(HWND &hwnd);
