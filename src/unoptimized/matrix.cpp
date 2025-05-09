#include "matrix.h"
#include <iostream>
int main() {

  Matrix<int, 3, 3> A;

  A.init(std::vector({1, 2, 3, 4, 5, 6, 7, 8, 9}));

  std::cout << A << std::endl;
  Matrix<int, 3, 3> B;
  B.init(std::array<int, 9>({9, 8, 7, 6, 5, 4, 3, 2, 1}));

  Matrix<int, 3, 4> C;
  C.init(std::array<int, 12>({1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4}));

  std::cout << B << std::endl;
  std::cout << A + B << std::endl;
  std::cout << A - B << std::endl;
  std::cout << A * C << std::endl;

  std::cout << C.transpose() << std::endl;

  std::cout << A.sum() << std::endl;
  std::cout << A.sumOverRow() << std::endl;
}
