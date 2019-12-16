//
// Created by acer on 15.12.2019.
//

#include <cmath>
#include "IterationMethod.h"
/// инициализируем метод итераций, из графического метода находим пригодную
/// для данного корня(ей)
IterationMethod::IterationMethod(std::initializer_list<float> coefs, float c) {
  int size = coefs.size();
  function.resize(size);
    /// записываем вектор функции, пригодной для итерации, по Формуле 3
  for (int i = 0, k = size - 1; i < size; ++i, k--) {
    function[k] = *(coefs.begin() + i) * c;
  }

  function[1]++;
}
/// получение корня методом итераций по Формуле 4
float IterationMethod::getX(float x0) {
  float xPrev = x0;
  float xNext = multiply(function, xPrev);
    /// повторяем итерации, пока не станет истинной неравенство Формулы 2
  while (fabs(xPrev - xNext) > E) {
    xPrev = xNext;
    xNext = multiply(function, xPrev);
  }
  return xNext;
}
