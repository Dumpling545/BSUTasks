#include "barchart.h"
BarChart::BarChart(){
}
int BarChart::getBarDrawingHeight(HDC &hdc, RECT drawingArea){
    return  (drawingArea.bottom - drawingArea.top) - getMaxLastNameSize(hdc).cx;
}
void BarChart::draw(HDC &hdc, RECT drawingArea){
    /*init variables*/
    int barWidth = (drawingArea.right - drawingArea.left) / info.size();
    int barHeight;
    double maxWeight = getMaxWeight();
    double weightSum = getWeightSum();
    int fontWidth = text_size / 1.5;
    int fontHeight = fontWidth * 1.5;
    HFONT font = CreateFont(fontHeight,
                            fontWidth,
                            900,0,10,FALSE,FALSE,FALSE,
                            DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                            CLIP_DEFAULT_PRECIS,PROOF_QUALITY,
                            VARIABLE_PITCH,TEXT("Times New Roman"));
    SelectObject(hdc, font);
    int maxHeight = getBarDrawingHeight(hdc, drawingArea);
    for(int i = 0; i < info.size(); i++){
        /*draw bar*/
        COLORREF color = RGB(red_coef*rand()%256,
                        green_coef*rand()%256,
                        blue_coef*rand()%256);
        HBRUSH brush = CreateSolidBrush(color);
        SelectObject(hdc, brush);
        barHeight = maxHeight * (info[i].totalWeight/maxWeight);
        Rectangle(hdc, drawingArea.left + i*barWidth, drawingArea.bottom - 1,
                  drawingArea.left +  (i + 1) * barWidth,
                  drawingArea.bottom - barHeight);
        DeleteObject(brush);
        /*draw signature*/
        SIZE _size;
        double percentage = info[i].totalWeight / weightSum;
        std::string str = getSignature(info[i].lastName, percentage);
        GetTextExtentPoint32(hdc, _T(str.c_str()), str.size(), &_size);
        SetTextColor(hdc, color);
        TextOut(hdc, margin + drawingArea.left + i * barWidth +
                (barWidth - _size.cy)/ 2,
                drawingArea.bottom - barHeight - 1,
                 _T(str.c_str()), str.size());
    }
    DeleteObject(font);
}
