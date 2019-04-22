#pragma once
#include <windows.h>
#include <tchar.h>
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void draw(HWND &hwnd);
void drawDiagrams(HDC &hdc, RECT rect);
std::string getSignature(std::string lastName, double percentage);
