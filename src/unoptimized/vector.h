#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <memory>
#include <ostream>

template <typename T, size_t N> class Vector : public std::array<T, N> {

public:
  T sum() {
    T acc = 0;
    for (int i = 0; i < N; i++) {
      acc += (*this)[i];
    }
    return acc;
  };

  T mean() { return sum() / N; };

  template <typename K, size_t M> Vector<T, N> operator+(Vector<K, M> &other) {
    assert(M == N);
    Vector<T, N> res;

    for (int i = 0; i < N; i++) {
      res[i] = (*this)[i] + other[i];
    }

    return res;
  };
};

template <typename T, size_t N>
std::ostream &operator<<(std::ostream &os, Vector<T, N> const &vec) {
  os << "{";

  for (int i = 0; i < N - 1; i++) {
    os << vec[i] << ", ";
  }
  os << vec[N - 1] << "}";

  return os;
};
