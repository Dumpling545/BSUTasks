#include "triangleController.h"
long double TriangleController::precision = 0.0000000001;
Triangle TriangleController::largestTriangle(Triangle * triangles, int length){
    Triangle res = Triangle(triangles[0]);
    for(int i = 0; i < length; i++){
        if(computeArea(res) < computeArea(triangles[i])){
           // delete res;
            res = Triangle(triangles[i]);
        }
    }
    return res;
}
long double TriangleController::computeArea(Triangle triangle){
    long double edges[3];
    long double w, h;
    long double halfPerimeter = 0;
    for(int i = 0; i < 3; i++){
        w = triangle.points[(i+1) % 3].x - triangle.points[i].x;
        h = triangle.points[(i+1) % 3].y - triangle.points[i].y;
        edges[i] = sqrt(w*w + h*h);
        halfPerimeter += edges[i];
    }
    halfPerimeter/=2;
    long double result = halfPerimeter;
    for(int i = 0; i < 3; i++){result *= (halfPerimeter - edges[i]);}
    return sqrt(result);
}
void TriangleController::moveTriangle(Triangle &triangle, long double x, long double y){
    for(int i = 0; i < 3; i++){
        triangle.points[i].x += x;
        triangle.points[i].y += y;
    }
}
bool TriangleController::contains(const Triangle container, const Triangle content){
    if(computeArea(container) < computeArea(content)){
        return false;
    } else {
        bool res = true;
        Triangle * temp;
        for(int i = 0; i < 3; i++){
            long double sum = 0;
            for(int j = 0; j < 3; j++){
                //delete temp;
                temp = new Triangle(container);
                //delete temp.points[j];
                temp->points[j] = Point(content.points[i]);
                sum += computeArea(*temp);
            }
            long double delta = ceil((computeArea(container) - sum)/precision)*precision;
            if(delta < 0){
                res = false;
                break;
            }
        }
        return res;
    }
}
 void TriangleController::printTriangle(const Triangle tr, ostream& _fout){
    _fout << "Triangle: ((";
    for(int i = 0; i < 3; i++){
        _fout<< tr.points[i].x << ", " << tr.points[i].y<<")";
        if(i != 2){_fout << ", (";}
        else {_fout << ")";}
    }
}
