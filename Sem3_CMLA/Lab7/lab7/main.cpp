#include <iostream>
#include <iomanip>
#include "NewtonsMethod.h"
#include "IterationMethod.h"
#include "BisectionMethod.h"

int main() {
  NewtonsMethod derivativeNewton({2, -60, -2740, 63075});
  IterationMethod derivativeIterationMinus({2, -60, -2740, 63075}, -1e-6);
  IterationMethod derivativeIterationPlus({2, -60, -2740, 63075}, 1e-6);

  std::cout << std::fixed << std::setprecision(11) <<
                                        derivativeNewton.getX(-35) << std::endl;
  std::cout << std::fixed << std::setprecision(11) <<
                                        derivativeNewton.getX(21) << std::endl;
  std::cout << std::fixed << std::setprecision(11) <<
                                        derivativeNewton.getX(45) << std::endl;

  std::cout << std::fixed << std::setprecision(11) <<
                                derivativeIterationMinus.getX(-35) << std::endl;
  std::cout << std::fixed << std::setprecision(11) <<
                                derivativeIterationPlus.getX(20) << std::endl;
  std::cout << std::fixed << std::setprecision(11) <<
                                derivativeIterationMinus.getX(45) << std::endl;

  NewtonsMethod funcNewtonRoot({1, -40, -2740, 126150, -3.52605e+6});
  BisectionMethod funcBisecRoot({1, -40, -2740, 126150, -3.52605e+6});

  std::cout << std::fixed << std::setprecision(11) <<
                                        funcNewtonRoot.getX(-60) << std::endl;
  std::cout << std::fixed << std::setprecision(11) <<
                                    funcBisecRoot.getX(-60, -55) << std::endl;

  std::cout << std::fixed << std::setprecision(11) <<
                                        funcNewtonRoot.getX(65) << std::endl;
  std::cout << std::fixed << std::setprecision(11) <<
                                        funcBisecRoot.getX(63, 67) << std::endl;
}
