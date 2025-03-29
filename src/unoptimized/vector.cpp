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

  std::cout << (a - b) << std::endl;
  std::cout << (b - a) << std::endl;

  std::cout << (a * b) << std::endl;
  std::cout << (b * a) << std::endl;

  std::cout << a.dot(b) << std::endl;
  std::cout << b.dot(a) << std::endl;

  Vector<float, 3> c = {1., 2., 3.};
  std::cout << a.norm() << std::endl;
  std::cout << c.norm() << std::endl;
  std::cout << b.norm() << std::endl;

  Vector<float, 3> x = {1, 0, 0};
  Vector<float, 3> y = {0, 1, 0};
  Vector<float, 3> z = {0, 0, 1};

  std::cout << b.proj(x) << std::endl;
  std::cout << b.proj(y) << std::endl;
  std::cout << b.proj(z) << std::endl;

  Vector<float, 2> test;
  std::cout << test << std::endl;

  std::cout << a.dense(b) << std::endl;
}
