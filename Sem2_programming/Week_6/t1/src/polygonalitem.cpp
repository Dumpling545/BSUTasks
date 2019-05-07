#include "polygonalitem.h"
PolygonalItem::PolygonalItem()
{
    //ctor
}
PolygonalItem::PolygonalItem(int x, int y,
                             std::vector<POINT> points, COLORREF color){
    this->x = x;
    this->y = y;
    this->points = std::vector<POINT>(points);
    this->color = color;
}
RECT PolygonalItem::border(){
    RECT rect;
    HRGN poly = CreatePolygonRgn(&points[0], points.size(), WINDING);
    GetRgnBox(poly, &rect);
    OffsetRect(&rect, x, y);
    return rect;
}
void PolygonalItem::draw(HDC &hdc){
    HBRUSH brush = CreateSolidBrush(color);
    HRGN poly = CreatePolygonRgn(&points[0], points.size(), WINDING);
    OffsetRgn(poly, x, y);
    FillRgn(hdc, poly, brush);
}
void PolygonalItem::onReverse(){
    for(int i = 0; i < points.size(); i++){
        points[i].x*=-1;
    }
}
void PolygonalItem::move(int dx, int dy){
    x+=dx;
    y+=dy;
}
