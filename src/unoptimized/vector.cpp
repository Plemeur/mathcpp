#include "vector.h"
#include <iostream>

int main() {
  Vector<int, 3> a = {1, 2, 3};
  std::cout << a.sum() << std::endl;
  std::cout << a.mean() << std::endl;

  Vector<float, 3> b = {1.5, 2.3, 3.1};
  std::cout << b.sum() << std::endl;
  std::cout << b.mean() << std::endl;

  std::cout << (a + b) << std::endl;
  std::cout << (b + a) << std::endl;
}
