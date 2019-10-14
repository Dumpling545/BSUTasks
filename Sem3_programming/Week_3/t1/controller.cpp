#include "BaseController.h"
INT_PTR CALLBACK  BaseController::handle(HWND hDlg,
                                             UINT message,
                                             WPARAM wParam,
                                             LPARAM lParam){
    switch(message){
        case WM_COMMAND:
            switch(LOWORD(wParam)){
                case ID_REFRESH:
                    onRefresh(hDlg);
                    break;
                case ID_ADD:
                    onAddElement(hDlg);
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hDlg);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return TRUE;
            break;
    }
    return FALSE;
}

Controller::Controller(){
    model = new Model();
}
void Controller::onRefresh(HWND hDlg){
    InputInfo input = IOService::unpackRefreshInfo(hDlg);
    OutputInfo output = model->refresh(input);
    IOService::sendOutput(hDlg, output);
}
void Controller::onAddElement(HWND hDlg){
    Element * elem = IOService::unpackAddElementInfo(hDlg);
    model->addElement(elem);
}
