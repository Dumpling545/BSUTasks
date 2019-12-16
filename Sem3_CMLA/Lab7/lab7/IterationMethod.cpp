//
// Created by acer on 15.12.2019.
//

#include <cmath>
#include "IterationMethod.h"
/// �������������� ����� ��������, �� ������������ ������ ������� ���������
/// ��� ������� �����(��)
IterationMethod::IterationMethod(std::initializer_list<float> coefs, float c) {
  int size = coefs.size();
  function.resize(size);
    /// ���������� ������ �������, ��������� ��� ��������, �� ������� 3
  for (int i = 0, k = size - 1; i < size; ++i, k--) {
    function[k] = *(coefs.begin() + i) * c;
  }

  function[1]++;
}
/// ��������� ����� ������� �������� �� ������� 4
float IterationMethod::getX(float x0) {
  float xPrev = x0;
  float xNext = multiply(function, xPrev);
    /// ��������� ��������, ���� �� ������ �������� ����������� ������� 2
  while (fabs(xPrev - xNext) > E) {
    xPrev = xNext;
    xNext = multiply(function, xPrev);
  }
  return xNext;
}
