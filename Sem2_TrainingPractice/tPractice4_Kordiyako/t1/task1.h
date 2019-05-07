#pragma once
#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
#include <windowsx.h>
#include <functional>
extern LPSTR input_str;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
struct GraphPoint;
void draw(HWND &hwnd);

void drawRect(HDC &hdc);
void drawFunctionGraph(HDC &hdc, RECT rect);

void drawAxes(HDC &hdc, RECT rect, POINT origin);
void drawFunction(HDC &hdc, RECT rect);
void drawPointerToAxes(HDC &hdc, RECT rect, POINT origin);
void drawScalesOfAxes(HDC &hdc, RECT rect, POINT origin);
void drawPointAtGraph(HDC &hdc, RECT rect, POINT origin);

void onLButtonDown(HWND &hwnd, LPARAM lParam);
void onLButtonUp(HWND &hwnd, LPARAM lParam);
void onMouseMove(HWND &hwnd, LPARAM lParam);
void onKeyDown(HWND &hwnd, WPARAM wParam);

void resizeAxes(RECT rect);
void resizeAxesToDefault();

POINT getOriginAtWindow(RECT rect);

GraphPoint pointToGraphpoint(int x, int y, RECT rect);
POINT graphpointToPoint(double g_x, double g_y, RECT rect);

void fillWithCoordinate(std::string &s, double coor);
