#include <iostream>
#include <iomanip>
#include <vector>
/// ��������� ��� ����� �������� �������� ��� ��������-�������� �������
struct FunctionItem{
    double argument;
    double value;
};
/** Enum, ������������ ��� ����������� ������ �������������.
    � �������� �������� ����� enum ����� �������  2^p - 1,
    ��e p -- ������� ��������������� ������������ ������. */
enum IntegralApproximationType{
    TRAPEZOIDAL_RULE = 3,
    SIMPSONS_METHOD = 15
};
/** C������� ������� �� ������� x ���������� � ������� f �������� �������.
    ��� ���������� ������ �������� � ������� x ������ ������ ����������.
*/
std::vector<FunctionItem> createFunctionItemVector(double * f,
                                                   double * x,
                                                   int n){
    std::vector<FunctionItem> items(n);
    for(int i = 0; i < n; i++){
        items[i].argument = x[i];
        items[i].value = f[i];
    }
    return items;
}
/** ������� ������������ �������� ���������.
    ������� �������� items � ����� �������� type ���������� ��� ���������.
    ��� ���������� ������ � ������� items �������� ������ ���� �������������
    �� ����������� argument.*/
double computeIntegralApproximation(const std::vector<FunctionItem> items,
                                    IntegralApproximationType type){
    double integral = 0;
    double h;
    switch(type){
        case TRAPEZOIDAL_RULE:
            for(int k = 0; k < items.size() - 1;k++){
                h = items[k + 1].argument - items[k].argument;
                integral +=  0.5 * h * (items[k + 1].value + items[k].value);
            }
            break;
        case SIMPSONS_METHOD:
            /** ��� ���������� ������ ������ ��������
                �� 2-�, 5-�, ..., (3*k + 2)-� ��������� �������
                �������� argument ������ ������������ �������� �����
                ���������� argument ���� �������� �����.
            */
            for(int k = 1; k < items.size() - 1;k+=2){
                h = items[k + 1].argument - items[k - 1].argument;
                integral += h * (items[k + 1].value + 4 * items[k].value + items[k - 1].value) / 6.0;
            }
            break;
    }
    return integral;
}
/** ��������� ���������� ������������� initialApproximation �������������� ����������.
    � ����� ����� ��������� ������� �������� items � ����� ������������� type.
    ������������, ��� � ������� items �������� ������������� �� ����������� argument,
    � �����, ��� ����� ��������������.
*/
double improveIntegralApproximationWithRichardsonExtrapolation(const std::vector<FunctionItem> items,
                                                             double initialApproximation,
                                                             IntegralApproximationType type){
    double improvedIntegral = initialApproximation;
    /// �������� ����� ������� � ����������� � ��� ���� ����� ���������.
    std::vector<FunctionItem> itemsWithDoubledStepSize((items.size() + 1)/2);
    for(int i = 0; i < itemsWithDoubledStepSize.size(); i++){
        itemsWithDoubledStepSize[i] = items[2*i];
    }
    /// ������� ������������� ��������������� ������� type �� ����� �������.
    double doubledStepSizeIntegral = computeIntegralApproximation(itemsWithDoubledStepSize,
                                                                  type);
    /** ���������� type, ������ ����� �������� �������, ������ 2^p - 1
        (p -- ������� ��������������� ������������ �������).
    */
    improvedIntegral += (initialApproximation - doubledStepSizeIntegral) / type;
    return improvedIntegral;
}
int main()
{
    /// ����� ������ ��� ������ ����� � ��������� ������
    const int PRECISION = 10;
    int n = 9;
    double * x = new double[n]{0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875, 1};
    double * f = new double[n]{0, 0.12467, 0.247234, 0.364902, 0.473112, 0.563209, 0.616193, 0.579699, 0};
    std::vector<FunctionItem> items = createFunctionItemVector(f, x, n);

    double trapezoidal = computeIntegralApproximation(items, TRAPEZOIDAL_RULE);
    double trapezoidalImproved =
        improveIntegralApproximationWithRichardsonExtrapolation(items,
                                                                trapezoidal,
                                                                TRAPEZOIDAL_RULE);

    double simpsons = computeIntegralApproximation(items, SIMPSONS_METHOD);
    double simpsonsImproved =
        improveIntegralApproximationWithRichardsonExtrapolation(items,
                                                                simpsons,
                                                                SIMPSONS_METHOD);
    std::cout << std::setprecision(PRECISION);
    std::cout << "Trapezoidal rule: "<< trapezoidal<< '\n';
    std::cout << "Trapezoidal rule improved with Richardson extrapolation: ";
    std::cout << trapezoidalImproved << '\n';
    std::cout << "Simpson's method: "<< simpsons<< '\n';
    std::cout << "Simpson's method improved with Richardson extrapolation: ";
    std::cout << simpsonsImproved << '\n';
    return 0;
}
