#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
#include <commdlg.h>
#include <iostream>
#include <answerform.h>
#include "pollfactory.h"
#include "resources/resource.h"
#include "poll.h"
INT_PTR CALLBACK DlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void draw(HWND &hwnd);
void drawText(HDC &hdc, RECT wRect);
void addAnswers(HWND& hdlg);
void initDialog(HWND &hdlg);
void finalMessageBox(HWND &hwnd);
void writeAnswersInStream(std::ostream & out, std::string res);
INT_PTR questionDialogBox(HWND& hdlgCurrent);
INT_PTR nextQuestionDialogBox(HWND& hdlgCurrent);
INT_PTR prevQuestionDialogBox(HWND& hdlgCurrent);
void onLButtonDown(HWND &hwnd, WPARAM wParam, LPARAM lParam);
