#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <ostream>
#include <vector>

template <typename T, size_t N, std::size_t M> class Matrix {
private:
  const size_t nRows = N;
  const size_t nCols = M;
  std::array<T, N * M> data;

public:
  inline const T &operator()(const size_t i, const size_t j) const {
    assert((i < N) && (j < M));
    return data[i * M + j];
  };

  inline T &operator()(const size_t i, const size_t j) {
    assert((i < N) && (j < M));
    return data[i * M + j];
  };

  void init(const std::vector<T> &initData) {
    assert(initData.size() == N * M);

    // that dumb, memcpy the stuff
    for (size_t i = 0; i < N * M; i++) {
      data[i] = initData[i];
    }
  }
  void init(const std::array<T, N * M> &initData) { data = initData; }

  Matrix<T, N, M> operator+(const Matrix<T, N, M> &other) {
    Matrix<T, N, M> res;
    for (int i = 0; i < N * M; i++) {
      res.data[i] = data[i] + other.data[i];
    }

    return res;
  }

  Matrix<T, N, M> operator-(const Matrix<T, N, M> &other) {
    Matrix<T, N, M> res;
    for (int i = 0; i < N * M; i++) {
      res.data[i] = data[i] - other.data[i];
    }

    return res;
  }

  template <size_t L> Matrix<T, N, L> operator*(const Matrix<T, M, L> &other) {
    Matrix<T, N, L> res;

    // C_ik = SUM_j A_ij * B_jk
    for (size_t i = 0; i < N; i++) {
      for (size_t k = 0; k < L; k++) {
        res(i, k) = 0;
        for (size_t j = 0; j < M; j++) {
          res(i, k) += (*this)(i, j) * other(j, k);
        }
      }
    }
    return res;
  }

  Matrix<T, M, N> transpose() {
    Matrix<T, M, N> res;

    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        res(j, i) = (*this)(i, j);
      }
    }
    return res;
  }

  static Matrix<T, M, N> transpose(Matrix<T, N, M> &mat) {
    return mat.transpose();
  };
};

template <typename T, size_t N, size_t M>
std::ostream &operator<<(std::ostream &os, const Matrix<T, N, M> &mat) {
  os << "[";
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M - 1; j++) {
      os << mat(i, j) << ", ";
    }
    if (i != (N - 1))
      os << mat(i, M - 1) << "\n ";
  }
  os << mat(N - 1, M - 1) << " ]";

  return os;
}
