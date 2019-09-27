#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <sstream>
#include "resources/resource.h"
#include "set.h"
#include "setiterator.h"
#include "visitor.h"
#include "BaseController.h"
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void refresh(HWND hDlg);
