#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <memory>
#include <ostream>

/*	Note to self:
 *	Need to check if those template I can actually verify the
 *	type to take the one with the high presicion, because while it makes
 *	sense to me to use the type of the first operand, results are weird.
 *
 *	Should add copy constructor from different types ?
 *
 *	probably never use the int version unless it's just mult/add
 *
 *	don't remember why I template the size of the other vector in the
 *	basic operation, does not make sense
 */

template <typename T, size_t N> class Vector : public std::array<T, N> {

public:
  T sum() const {
    T acc = 0;
    for (int i = 0; i < N; i++) {
      acc += (*this)[i];
    }
    return acc;
  };

  T mean() const { return sum() / N; };

  template <typename K, size_t M>
  Vector<T, N> operator+(const Vector<K, M> &other) const {
    assert(M == N);
    Vector<T, N> res;

    for (int i = 0; i < N; i++) {
      res[i] = (*this)[i] + other[i];
    }

    return res;
  };

  template <typename K, size_t M>
  Vector<T, N> operator-(const Vector<K, M> &other) const {
    assert(M == N);
    Vector<T, N> res;

    for (int i = 0; i < N; i++) {
      res[i] = (*this)[i] - other[i];
    }

    return res;
  };

  template <typename K, size_t M>
  Vector<T, N> operator*(const Vector<K, M> &other) const {
    assert(M == N);
    Vector<T, N> res;

    for (int i = 0; i < N; i++) {
      res[i] = (*this)[i] * other[i];
    }

    return res;
  };

  template <typename K, size_t M>
  Vector<T, N> operator/(const Vector<K, M> &other) const {
    assert(M == N);
    Vector<T, N> res;

    // Should check for 0 here probably
    for (int i = 0; i < N; i++) {
      res[i] = (*this)[i] / other[i];
    }

    return res;
  };

  template <typename K, size_t M> T dot(const Vector<K, M> &other) const {

    assert(M == N);
    T res = 0;

    for (int i = 0; i < N; i++) {
      res += (*this)[i] * other[i];
    }

    return res;
  };

  // Does not make sense to use the templated type for the norm
  // since the sqrt is defined only for floats in C.
  T norm() const {
    T norm = 0;

    for (int i = 0; i < N; i++) {
      norm += (*this)[i] * (*this)[i];
    }

    return std::sqrt(norm);
  }

  template <typename K, size_t M> T proj(const Vector<K, M> &other) const {
    assert(M == N);
    return dot(other) / (other.norm());
  }

  // Now that I think of it, it's kind of similar to a matrix multiplication
  // with a sum after
  template <typename K, size_t M>
  Vector<T, N> dense(const Vector<K, M> &other) const {
    Vector<T, N> res;

    for (int i = 0; i < N; i++) {
      res[i] = 0;
      for (int j = 0; j < M; j++) {
        res[i] += (*this)[i] * other[j];
      }
    }
    return res;
  }

  T dist_L2(const Vector<T, N> other) const {
    T res = 0;

    for (int i = 0; i < N; i++) {
      res += pow(((*this)[i] - other[i]), 2);
    }

    return sqrt(res);
  }
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
