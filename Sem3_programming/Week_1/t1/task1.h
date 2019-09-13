#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include "resources/resource.h"
#include "set.h"
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void draw(HWND &hwnd);
