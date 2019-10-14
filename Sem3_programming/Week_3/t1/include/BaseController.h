#pragma once
#include "model.h"
#include "ioservice.h"
class BaseController
{
    public:
        virtual INT_PTR CALLBACK handle(HWND hDlg,
                                        UINT message,
                                        WPARAM wParam,
                                        LPARAM lParam) final;
        virtual ~BaseController() = default;
    protected:
        virtual void onRefresh(HWND hDlg) = 0;
        virtual void onAddElement(HWND hDlg) = 0;
        Model * model;
};
class Controller : public BaseController {
    public:
        Controller();
    protected:
    virtual void onRefresh(HWND hDlg);
    virtual void onAddElement(HWND hDlg);
};
