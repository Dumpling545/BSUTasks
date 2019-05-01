#pragma once
#include <windows.h>
#include <tchar.h>
#include <commdlg.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "diagram.h"
#include "barchart.h"
#include "filemanager.h"
#include "fisherman.h"
#include "piechart.h"
#include "../resources/resource.h"
INT_PTR CALLBACK DlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void draw(HWND &hwnd);
void drawDiagrams(HDC &hdc, RECT rect);
void onCommand(HWND &hwnd, WPARAM wParam);
std::string getSignature(std::string lastName, double percentage);
