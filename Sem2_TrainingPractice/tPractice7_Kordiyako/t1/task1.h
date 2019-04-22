#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <commdlg.h>
#include "include/car.h"
#include "resources/resource.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Dialog1(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void draw(HWND &hwnd);
void drawCar(HDC &hdc);
void onCreate(HWND &hwnd);
void onTimer(HWND &hwnd);
void onRButttonDown();
void onCommand(HWND &hwnd, WPARAM wParam);
POINT carCurve(int t);
