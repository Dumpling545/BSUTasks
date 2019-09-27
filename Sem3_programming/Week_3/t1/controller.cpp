#include "BaseController.h"
Controller::handle(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_COMMAND:
            switch(LOWORD(wParam)){
                case ID_REFRESH:
                    onRefresh(hDlg);
                    break;
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
    InputInfo input = IOService::unpackInput(hDlg);
    OutputInfo output = model->refresh(input);
    IOService::sendOutput(hDlg, output);
}
