#include <iostream>
#include <fstream>
#include "triangleController.h"
#include "triangle.h"
using namespace std;
/**
    На основании разобранной в этом разделе задачи 1.2 создайте приложение для решения задачи:
    «Для некоторого множества заданных координатами своих вершин треугольников найти треугольник
    максимальной площади (если максимальную площадь имеют несколько треугольников, то найти первый из них).
    Предусмотреть возможность перемещения треугольников и проверки включения одного треугольника в другой».
*/
ifstream fin("input.txt");
ofstream fout("output.txt");
bool isCorrectInputFile(ifstream &_fin){
    if(_fin &&  _fin.peek() != ifstream::traits_type::eof()){
        return true;
    } else {
        cout << "Input file doesn't exist or empty" << endl;
        return false;
    }
}
int main()
{
    if(isCorrectInputFile(fin)){
        int N;
        fin >> N;
        Triangle * triangles = new Triangle[N];
        for(int i = 0; i < N; i++){
            for(int j = 0; j < 3; j++){
                //points[j] = Point();
                fin >> triangles[i].points[j].x >> triangles[i].points[j].y;
            }
        }
        Triangle largerst = TriangleController::largestTriangle(triangles, N);
        fout << "Largest ";
        TriangleController::printTriangle(largerst, fout);
        fout << endl << endl << "Contains: "<<endl;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if( i!= j && TriangleController::contains(triangles[i], triangles[j])){
                    TriangleController::printTriangle(triangles[i], fout);
                    fout << " contains ";
                    TriangleController::printTriangle(triangles[j], fout);
                    fout << endl;
                }
            }
        }
        fout << endl << "Move ";
        TriangleController::printTriangle(triangles[6], fout);
        fout << " by vector(0.0001, 0.0001): Return ";
        TriangleController::moveTriangle(triangles[6], 0.0001, 0.0001);
        TriangleController::printTriangle(triangles[6], fout);
    }
    return 0;
}
