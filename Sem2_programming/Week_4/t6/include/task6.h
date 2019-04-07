#pragma once
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <cmath>
#include "timetable.h"
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

bool isCorrectInputFile(std::ifstream &_fin);
void readTimetableFromFile(std::string filename);

COLORREF chooseLectureColor(char c);
void drawCellTitles(HDC &hdc, RECT rect, COLORREF bkColor,
                    std::string textTop ="", std::string textCenter = "");
void drawCell(HDC &hdc, int rowIndex, int colIndex,
              int cellWidth, int cellHeight,
              int left, int top, COLORREF color,
              std::string textTop ="", std::string textCenter = "");
void drawTimetable(HDC &hdc, Timetable timetable, RECT rect);
void draw(HWND &hwnd);
