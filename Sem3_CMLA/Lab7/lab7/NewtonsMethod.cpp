//
// Created by acer on 15.12.2019.
//
#include <cmath>
#include "NewtonsMethod.h"

/// инициализация функции и её производной
NewtonsMethod::NewtonsMethod(std::initializer_list<float> coefs) {
  int size = coefs.size();
  function.resize(size);
  derivative.resize(size - 1);
 ///записываем вектор функции (переворачиваем исходный)
  for (int i = 0, k = size - 1; i < size; ++i, k--) {
    function[k] = *(coefs.begin() + i);
  }
  /// записываем вектор производной нашей функции
  for (int i = size - 1; i > 0; --i) {
    derivative[i - 1] = function[i] * i;
  }
}
/// значение функции в точке
float NewtonsMethod::getFuncVal(float x) {
  return multiply(function, x);
}
/// значение производной в точке
float NewtonsMethod::getDerivVal(float x) {
  return multiply(derivative, x);
}
///метод Ньютона поиска корней
float NewtonsMethod::getX(float x0) {
  /** считаем по Формуле 1*/
  float xPrev = x0;
  float xNext = xPrev - getFuncVal(xPrev) / getDerivVal(xPrev);
  /// повторяем итерации, пока не станет истинным неравенство Формулы 2
  while(fabs(xPrev - xNext) > E) {
    xPrev = xNext;
    xNext = xPrev - getFuncVal(xPrev) / getDerivVal(xPrev);
  }

  return xNext;
}
