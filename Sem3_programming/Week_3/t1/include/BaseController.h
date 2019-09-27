#pragma once
#include "model.h"
#include "ioservice.h"
class BaseController
{
    public:
        virtual INT_PTR CALLBACK handle(HWND hDlg,
                                        UINT message,
                                        WPARAM wParam,
                                        LPARAM lParam) = 0;
        virtual ~BaseController() = default;
    protected:

        Model * model;
};
class Controller : public BaseController {
    public:
        Controller();
        virtual INT_PTR CALLBACK handle(HWND hDlg,
                                        UINT message,
                                        WPARAM wParam,
                                        LPARAM lParam);
    private:
    void onRefresh(HWND hDlg);

};
