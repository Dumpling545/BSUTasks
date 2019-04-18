#include "barchart.h"

BarChart::BarChart()
{
    //ctor
}
void BarChart::draw(HDC &hdc, RECT drawingArea){
    int barWidth = (drawingArea.right - drawingArea.left) / info.size();
    int chart_to_height_rate = 0.75;
    int barHeight;
    std::vector<FishermanInfo>::iterator  it =  (
                    std::max_element(
                        info.begin(),
                        info.end(),
                        [](FishermanInfo f1, FishermanInfo f2){
                                return f1.totalWeight < f2.totalWeight;
                        })
                    );
    double maxWeight = (*it).totalWeight;
    for(int i = 0; i < info.size(); i++){
        barHeight = chart_to_height_rate*(info[i].totalWeight / maxWeight);
    }
}
