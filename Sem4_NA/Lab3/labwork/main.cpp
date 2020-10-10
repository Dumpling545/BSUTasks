#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
struct Point {
    Point() {}
    Point(double x, std::vector<double> y) {
        this -> x = x;
        this -> y = y;
    }
    double x;
    std::vector<double> y;
};
///first task function with parameter g1Param
double g1Param = 3.0;
/// adapting non-vector function to use with vector-based method
std::vector<double> G1(double x, std::vector<double> u){
    return {g1Param*u[0]};
}
///second task function
std::vector<double> G2 (double x, std::vector<double> u) {
    return {u[1], -u[0]};
}
///third task function
std::vector<double> G3 (double x, std::vector<double> u) {
    return {98*u[0] + 198*u[1], -99*u[0]-199*u[1]};
}
///fourth task function with parameter g4Param in [1, 5]
double g4Param = 1.0;
std::vector<double> G4 (double x, std::vector<double> u) {
    return {1 + u[0]*u[0]*u[1] - (g4Param+1)*u[1], g4Param*u[0] - u[0]*u[0]*u[1]};
}
std::vector<double> getFirstHeunCoefficientVector(
                        std::vector<double> (*G) (double, std::vector<double>),
                        double xn, std::vector<double> un) {
    return G(xn, un);
}

std::vector<double> getSecondHeunCoefficientVector(
                        std::vector<double> (*G) (double, std::vector<double>),
                        double xn, std::vector<double> un,
                        double iterationStep,
                        std::vector<double> firstHeunCoefficientVector) {
    std::vector<double> param(un.size());
    for(int i = 0; i < un.size(); i++){
        param[i] = un[i] + firstHeunCoefficientVector[i] * (iterationStep / 3.0);
    }
    return G(xn + (iterationStep / 3.0), param);
}

std::vector<double> getThirdHeunCoefficientVector(
                        std::vector<double> (*G) (double, std::vector<double>),
                        double xn, std::vector<double> un,
                        double iterationStep,
                        std::vector<double> secondHeunCoefficientVector) {
    std::vector<double> param(un.size());
    for(int i = 0; i < un.size(); i++){
        param[i] = un[i] +
                    secondHeunCoefficientVector[i] * (2.0 * iterationStep / 3.0);
    }
    return G(xn + (2.0 * iterationStep / 3.0), param);
}

Point getHeunMethodIterationResult(std::vector<double> (*G) (double, std::vector<double>),
                                   Point previousIterationResult,
                                   double iterationStep){
    std::vector<double> firstHeunCoefficientVector =
    getFirstHeunCoefficientVector(G, previousIterationResult.x,
                         previousIterationResult.y);
    std::vector<double> secondHeunCoefficientVector =
                getSecondHeunCoefficientVector(G,
                                               previousIterationResult.x,
                                               previousIterationResult.y,
                                               iterationStep,
                                               firstHeunCoefficientVector);
    std::vector<double> thirdHeunCoefficientVector =
                getThirdHeunCoefficientVector(G,
                                              previousIterationResult.x,
                                              previousIterationResult.y,
                                              iterationStep,
                                              secondHeunCoefficientVector);
    std::vector<double> nextValue(previousIterationResult.y.size());
    for(int i = 0; i < previousIterationResult.y.size(); i++){
        nextValue[i] = previousIterationResult.y[i] +
                        (firstHeunCoefficientVector[i] +
                         3.0*thirdHeunCoefficientVector[i]) / 4.0 * iterationStep;
    }
    return Point(previousIterationResult.x + iterationStep, nextValue);
}

std::vector<Point> solveEquationSystem(double leftLimitPoint, double rightLimitPoint,
                     double iterationStep, std::vector<double> initialCondition,
                     std::vector<double> (*G)(double, std::vector<double>)) {
    int numberOfPoints =
            (int)trunc((rightLimitPoint - leftLimitPoint)/iterationStep) + 1;
    std::vector<Point> result(numberOfPoints);
    result[0] = Point(leftLimitPoint, initialCondition);
    for(int i = 1; i < numberOfPoints; i++){
        result[i] = getHeunMethodIterationResult(G,
                                                 result[i - 1],
                                                 iterationStep);
    }
    return result;
}
void printPhasePortraitInFile(const char* filename,  std::vector<Point> points){
    if(points.size() > 0){
        std::ofstream fout;
        fout.open(filename);
        int n = points[0].y.size();
        for(int i = 0; i < points.size(); i++){
           for(int j = 0; j < points[i].y.size(); j++){
                fout << points[i].y[j] << ' ';
           }
           fout << '\n';
        }
        fout.close();
    }
}
void printGraphInFile (const char* filename,  std::vector<Point> points){
    if(points.size() > 0){
        std::ofstream fout;
        fout.open(filename);
        for(int i = 0; i < points.size(); i++){
            fout << points[i].x;
            for(int j = 0; j < points[i].y.size(); j++){
                fout << ' ' << points[i].y[j];
            }
            fout << '\n';
        }
    }
}
double getError(std::vector<Point> approximation,
                std::vector<double> (*preciseSolution)(double)){
    if(approximation.size() > 0){
        int n = approximation[0].y.size();
        double maxDiff = 0;
        double diff = 0;
        for(int i = 0; i < n; i++){
           for(int k = 0; k < approximation.size(); k++){
                diff = std::abs(approximation[k].y[i] -
                                preciseSolution(approximation[k].x)[i]);
                if(diff > maxDiff) maxDiff = diff;
           }
        }
        return maxDiff;
    }
    return -1;
}
void printError(std::vector<Point> approximation,
                     std::vector<double> (*preciseSolution)(double)){
    std::cout << "    Error: "
        << getError(approximation,  preciseSolution) << '\n';
}
int main()
{
    double leftLimit = 0;
    double rightLimit = 2;
    double iterationStep = 0.05;

    std::cout << "Task 1A: {u' = "<<g1Param <<"*u; u(0) = 1}" <<
     " with interval ["<<
    leftLimit <<", " << rightLimit << "] and iteration step h = " <<
    iterationStep << '\n';
    std::vector<Point> task1a_result = solveEquationSystem(leftLimit,
                                                         rightLimit,
                                                         iterationStep, {1}, G1);
    printError(task1a_result,
        [](double x)->std::vector<double>{ return {exp(g1Param * x)}; });
    printGraphInFile("task1a.dat", task1a_result);

    g1Param = -3;
    std::cout << "Task 1B: {u' = "<<g1Param <<"*u; u(0) = 1}" <<
     " with interval ["<<
    leftLimit <<", " << rightLimit << "] and iteration step h = " <<
    iterationStep << '\n';
    std::vector<Point> task1b_result = solveEquationSystem(leftLimit,
                                                         rightLimit,
                                                         iterationStep, {1}, G1);
    printError(task1b_result,
        [](double x)->std::vector<double>{ return {exp(g1Param * x)}; });
    printGraphInFile("task1b.dat", task1b_result);

    g1Param = -20;
    iterationStep = 0.1;
    rightLimit = 3;
    std::cout << "Task 1C: {u' = "<<g1Param <<"*u; u(0) = 1}" <<
     " with interval ["<<
    leftLimit <<", " << rightLimit << "] and iteration step h = " <<
    iterationStep << '\n';
    std::vector<Point> task1c_result = solveEquationSystem(leftLimit,
                                                         rightLimit,
                                                         iterationStep, {1}, G1);
    printError(task1c_result,
        [](double x)->std::vector<double>{ return {exp(g1Param * x)}; });
    printGraphInFile("task1c.dat", task1c_result);

    iterationStep = 0.06;
    std::cout << "Task 1D: {u' = "<<g1Param <<"*u; u(0) = 1}" <<
     " with interval ["<<
    leftLimit <<", " << rightLimit << "] and iteration step h = " <<
    iterationStep << '\n';
    std::vector<Point> task1d_result = solveEquationSystem(leftLimit,
                                                         rightLimit,
                                                         iterationStep, {1}, G1);
    printError(task1d_result,
        [](double x)->std::vector<double>{ return {exp(g1Param * x)}; });
    printGraphInFile("task1d.dat", task1d_result);

    iterationStep = 0.01;
    std::cout << "Task 1E: {u' = "<<g1Param <<"*u; u(0) = 1}" <<
     " with interval ["<<
    leftLimit <<", " << rightLimit << "] and iteration step h = " <<
    iterationStep << '\n';
    std::vector<Point> task1e_result = solveEquationSystem(leftLimit,
                                                         rightLimit,
                                                         iterationStep, {1}, G1);
    printError(task1e_result,
        [](double x)->std::vector<double>{ return {exp(g1Param * x)}; });
    printGraphInFile("task1e.dat", task1e_result);

    iterationStep = 0.001;
    std::cout << "Task 1F: {u' = "<<g1Param <<"*u; u(0) = 1}" <<
     " with interval ["<<
    leftLimit <<", " << rightLimit << "] and iteration step h = " <<
    iterationStep << '\n';
    std::vector<Point> task1f_result = solveEquationSystem(leftLimit,
                                                         rightLimit,
                                                         iterationStep, {1}, G1);
    printError(task1f_result,
        [](double x)->std::vector<double>{ return {exp(g1Param * x)}; });
    printGraphInFile("task1f.dat", task1f_result);

    iterationStep = 0.01;
    std::cout << "Task 2: {u' = v, v' = -u; u(0) = v(0) = 1}" <<
     " with interval ["<<
    leftLimit <<", " << rightLimit << "] and iteration step h = " <<
    iterationStep << '\n';
    std::vector<Point> task2_result = solveEquationSystem(leftLimit,
                                                      rightLimit,
                                                      iterationStep, {1, 1}, G2);
    printError(task2_result,
               [](double x)->std::vector<double>{
                    return {sin(x) + cos(x),
                            cos(x) - sin(x)};
               });
    printPhasePortraitInFile("task2.dat", task2_result);

    std::cout << "Task 3: {u' = 98u + 198v, v' = -99u-199v; u(0) = v(0) = 1}" <<
     " with interval ["<<
    leftLimit <<", " << rightLimit << "] and iteration step h = " <<
    iterationStep << '\n';
    std::vector<Point> task3_result = solveEquationSystem(leftLimit,
                                                      rightLimit,
                                                      iterationStep, {1, 1}, G3);
    printError(task3_result,
               [](double x)->std::vector<double> {
                    return {4*exp(-x) - 3*exp(-100*x),
                            -2*exp(-x) + 3*exp(-100*x)};
                });
    printPhasePortraitInFile("task3.dat", task3_result);
    std::vector<Point> errorFunction;
    for(double step = 0.0245; step <= 0.0255; step+=0.0001){
        std::vector<Point> error_task3_result = solveEquationSystem(leftLimit,
                                                          rightLimit,
                                                          step,
                                                          {1, 1}, G3);
        double error = getError(error_task3_result,
                                [](double x)->std::vector<double> {
                                    return {4*exp(-x) - 3*exp(-100*x),
                                            -2*exp(-x) + 3*exp(-100*x)};
                                });
        errorFunction.push_back(Point(step, {error}));
    }
    printGraphInFile("stability_research.dat", errorFunction);
    rightLimit = 1000;
    iterationStep = 0.1;
    std::cout << "Task 4: {u' = 1 + u*u*v - (B+1)*v, v' = B*u - u*u*v; u(0) = v(0) = 1}" <<
     " with interval ["<<
    leftLimit <<", " << rightLimit << "] and iteration step h = " <<
    iterationStep << '\n';
    int i = 1;
    for(i = 1; i <= 5; i++){
        g4Param = i;
        char letter = 'A' + (i-1);
        std::cout << "Task 4" << letter << ": B = " << g4Param <<'\n';
        std::string filename("task4");
        filename+= letter;
        filename.append(".dat");
        std::vector<Point> task4_result = solveEquationSystem(leftLimit,
                                                      rightLimit,
                                                      iterationStep, {1, 1}, G4);
        printPhasePortraitInFile(filename.c_str(), task4_result);
    }
    return 0;
}
