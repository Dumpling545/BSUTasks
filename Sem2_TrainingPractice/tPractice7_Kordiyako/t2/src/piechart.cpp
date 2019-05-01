#include "../include/piechart.h"
PieChart::PieChart(){}
RECT PieChart::getPieDrawingArea(HDC &hdc, RECT drawingArea){
    SIZE s = getMaxLastNameSize(hdc);
    RECT result;
    result.top = drawingArea.top + s.cy + 2 * margin;
    result.bottom = drawingArea.bottom - s.cy - 2 * margin;
    result.right = drawingArea.right - s.cx - 2 * margin;
    result.left = drawingArea.left + s.cx + 2 * margin;
    return result;
}
void PieChart::draw(HDC &hdc, RECT drawingArea){
    /*init variables: loop variables*/
    double angle0 = 0, angle1 = 0, angle_text = 0;
    int x_text = 0, y_text = 0;
    double percentage = 0;
    COLORREF color;
    HBRUSH brush;
    /*init font*/
    HFONT font;
    font = CreateFont(text_size,
                        text_size/1.5,
                        0,0,10,FALSE,FALSE,FALSE,
                        DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                        CLIP_DEFAULT_PRECIS,PROOF_QUALITY,
                        VARIABLE_PITCH,TEXT("Times New Roman"));
    SelectObject(hdc, font);
    /*init variables: other variables*/
    double weightSum = getWeightSum();
    RECT pieDrawingArea = getPieDrawingArea(hdc, drawingArea);
    int x0 = (pieDrawingArea.right + pieDrawingArea.left) / 2;
    int y0 = (pieDrawingArea.top + pieDrawingArea.bottom) / 2;
    int r = std::min((pieDrawingArea.bottom - pieDrawingArea.top) / 2,
                     (pieDrawingArea.right - pieDrawingArea.left) / 2);

    /*draw piechart pie by pie*/
    for(int i = 0; i < info.size(); i++){
        /*init pie-and-signature color*/
        color = RGB(red_coef*rand()%256,
                    green_coef*rand()%256,
                    blue_coef*rand()%256);
        /*draw pie*/
        brush = CreateSolidBrush(color);
        percentage = info[i].totalWeight / weightSum;
        angle1 = angle0 + 2 * percentage*M_PI;
        SelectObject(hdc, brush);
        Pie(hdc, x0 - r, y0 - r, x0 + r, y0 + r, x0 + r*cos(angle1),
            y0 + r*sin(angle1), x0 + r*cos(angle0), y0 + r*sin(angle0));
        DeleteObject(brush);
        /*draw text: init signature, get signature size*/
        std::string text = getSignature(info[i].lastName, percentage);
        SIZE s;
        GetTextExtentPoint32(hdc, _T(text.c_str()), text.size(), &s);
        /*draw text: define location of signature*/
        angle_text = (angle0+angle1)/2.0;
        x_text = x0 + cos(angle_text)*r;
        y_text = y0 + sin(angle_text)*r;
        switch((int)(2 * angle_text / M_PI)){
            case 3:
                y_text -= s.cy;
            break;
            case 2:
                y_text -= s.cy;
                x_text -= s.cx;
            break;
            case 1:
                x_text -= s.cx;
            break;
        }
        /*draw text: final steps*/
        SetTextColor(hdc, color);
        TextOut(hdc, x_text, y_text, _T(text.c_str()), text.size());
        angle0 = angle1;
        DeleteObject(font);
    }
}
