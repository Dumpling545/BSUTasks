#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "BisectionMethod.h"
/// инициализация метода деления отрезка пополам
BisectionMethod::BisectionMethod(std::initializer_list<float> coefs) {
  int size = coefs.size();
  function.resize(size);
  ///записываем вектор функции (переворачиваем исходный)
  for (int i = 0, k = size - 1; i < size; ++i, k--) {
    function[k] = *(coefs.begin() + i);
  }
}
/// метод деления отрезков пополам на интервале [a, b]
float BisectionMethod::getX(float a, float b) {
  /**если образы обоих концов отрезка имеют один знак,
     то использование метода некорректно*/
  if (multiply(function, a) * multiply(function, b) > 0){
        throw std::invalid_argument("Invalid range");
  }

  float m;
 /** продолжаем деление пополам, пока длина отрезка не станет меньше (или равна)
     двойной точности
 */
  while (fabs(b - a) > 2 * E) {
    m = (a + b) / 2;
    ///находим значение функции в середине интервала
    float fM = multiply(function, m);
    if (fabs(fM) < E) return m;
    /**сдвигаем к середине тот конец, знак образа котороого совпадает со
       со знаком образа середины отрезка
    */
    (multiply(function, a) * fM < 0) ? b = m : a = m;
  }

  return (a + b) / 2;
}


