#pragma once
#include <sstream>
#include <windows.h>
#include <tchar.h>
#include "../resources/resource.h"
#include "inputinfo.h"
#include "outputelementinfo.h"
#include "outputinfo.h"
class IOService
{
    static const int DEFAULT_TCHAR_ARRAY_LENGTH = 200;
    public:
        static void sendOutput(HWND hDlg, OutputInfo output);
        static InputInfo unpackInput(HWND hDlg);
    private:
        IOService(){}
};
