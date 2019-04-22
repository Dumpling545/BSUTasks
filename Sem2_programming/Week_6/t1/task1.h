#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <utility>
#include "include/car.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void draw(HWND &hwnd);
void drawCar(HDC &hdc);
void onCreate(HWND &hwnd);
void onTimer(HWND &hwnd);
void onRButttonDown();
POINT carCurve(int t);
