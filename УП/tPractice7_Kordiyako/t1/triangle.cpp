#include "triangle.h"
Triangle::Triangle(Point * points){
    for(int i = 0; i < 3; i++){
        this->points[i] = points[i];
    }
}
Triangle::Triangle(const Triangle &t){
    for(int i = 0; i < 3; i++){
       // delete this->points[i];
        this->points[i] = Point(t.points[i]);
    }
}
Triangle::Triangle(){
    for(int i = 0; i < 3; i++){
        points[i] = Point();
    }
}
