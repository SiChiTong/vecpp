//  Copyright 2018 Francois Chabot
//  (francois.chabot.dev@gmail.com)
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef VECPP_VEC_H_INCLUDED
#define VECPP_VEC_H_INCLUDED

#include "vecpp/config.h"

#include <array>
#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <iostream>

namespace VECPP_NAMESPACE {

template <typename T, std::size_t len>
struct Vec {
 public:
  using value_type = T;

  constexpr std::size_t size() const { return len; }

  constexpr T& at(std::size_t i) {
    if (i >= len) {
      throw std::out_of_range("out of range vector access");
    }
    return data_[i];
  }

  constexpr const T& at(std::size_t i) const {
    if (i >= len) {
      throw std::out_of_range("out of range vector access");
    }
    return data_[i];
  }

  constexpr T& operator[](std::size_t i) {
    assert(i < len);
    return data_[i];
  }
  constexpr const T& operator[](std::size_t i) const {
    assert(i < len);
    return data_[i];
  }

  constexpr T* data() { return data_.data(); }
  constexpr const T* data() const { return data_.data(); }

  // Left public for aggregate initialization.
  std::array<T, len> data_;
};

// Vectors may as well be ranges.
template <typename T, std::size_t len>
constexpr T* begin(Vec<T, len>& v) {
  return v.data();
}

template <typename T, std::size_t len>
constexpr T* end(Vec<T, len>& v) {
  return v.data() + len;
}

template <typename T, std::size_t len>
constexpr const T* begin(const Vec<T, len>& v) {
  return v.data();
}

template <typename T, std::size_t len>
constexpr const T* end(const Vec<T, len>& v) {
  return v.data() + len;
}

// std::ostream support
template <typename T, std::size_t L>
std::ostream& operator<<(std::ostream& stream, const Vec<T, L>& vec) {
  stream << "(";

  bool first = true;
  for(const auto& v : vec) {
    if(!first) {
      stream << ", ";
    }
    else {
      first = false;
    }

    stream << v;
  }

  stream << ")";
  return stream;
}

// Comparisons
template <typename T, std::size_t L>
constexpr bool operator==(const Vec<T, L>& lhs, const Vec<T, L>& rhs) {
  for (std::size_t i = 0; i < L; ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

template <typename T, std::size_t L>
constexpr bool operator!=(const Vec<T, L>& lhs, const Vec<T, L>& rhs) {
  for (std::size_t i = 0; i < L; ++i) {
    if (lhs[i] != rhs[i]) {
      return true;
    }
  }
  return false;
}

// Unary Operators
template <typename T, std::size_t L>
constexpr Vec<T, L> operator-(const Vec<T, L>& rhs) {
  Vec<T, L> result = {};
  for (std::size_t i = 0; i < L; ++i) {
    result[i] = -rhs[i];
  }
  return result;
}

// Binary Operators
template <typename T, std::size_t L>
constexpr Vec<T, L>& operator+=(Vec<T, L>& lhs, const Vec<T, L>& rhs) {
  for (std::size_t i = 0; i < L; ++i) {
    lhs[i] += rhs[i];
  }
  return lhs;
}

template <typename T, std::size_t L>
constexpr Vec<T, L> operator+(const Vec<T, L>& lhs, const Vec<T, L>& rhs) {
  Vec<T, L> result = lhs;
  result += rhs;
  return result;
}

template <typename T, std::size_t L>
constexpr Vec<T, L>& operator-=(Vec<T, L>& lhs, const Vec<T, L>& rhs) {
  for (std::size_t i = 0; i < L; ++i) {
    lhs[i] -= rhs[i];
  }
  return lhs;
}

template <typename T, std::size_t L>
constexpr Vec<T, L> operator-(const Vec<T, L>& lhs, const Vec<T, L>& rhs) {
  Vec<T, L> result = lhs;
  result -= rhs;
  return result;
}

template <typename T, std::size_t L>
constexpr Vec<T, L>& operator*=(Vec<T, L>& lhs, const Vec<T, L>& rhs) {
  for (std::size_t i = 0; i < L; ++i) {
    lhs[i] *= rhs[i];
  }
  return lhs;
}

template <typename T, std::size_t L>
constexpr Vec<T, L> operator*(const Vec<T, L>& lhs, const Vec<T, L>& rhs) {
  Vec<T, L> result = lhs;
  result *= rhs;
  return result;
}

template <typename T, std::size_t L>
constexpr Vec<T, L>& operator/=(Vec<T, L>& lhs, const Vec<T, L>& rhs) {
  for (std::size_t i = 0; i < L; ++i) {
    lhs[i] /= rhs[i];
  }
  return lhs;
}

template <typename T, std::size_t L>
constexpr Vec<T, L> operator/(const Vec<T, L>& lhs, const Vec<T, L>& rhs) {
  Vec<T, L> result = lhs;
  result /= rhs;
  return result;
}

template <typename T, std::size_t L>
constexpr Vec<T, L>& operator*=(Vec<T, L>& lhs, const T& rhs) {
  for (std::size_t i = 0; i < L; ++i) {
    lhs[i] *= rhs;
  }
  return lhs;
}

template <typename T, std::size_t L>
constexpr Vec<T, L> operator*(const Vec<T, L>& lhs, const T& rhs) {
  Vec<T, L> result = lhs;
  result *= rhs;
  return result;
}

template <typename T, std::size_t L>
constexpr Vec<T, L> operator*(const T& lhs, const Vec<T, L>& rhs) {
  return rhs * lhs;
}

template <typename T, std::size_t L>
constexpr Vec<T, L>& operator/=(Vec<T, L>& lhs, const T& rhs) {
  for (std::size_t i = 0; i < L; ++i) {
    lhs[i] /= rhs;
  }
  return lhs;
}

template <typename T, std::size_t L>
constexpr Vec<T, L> operator/(const Vec<T, L>& lhs, const T& rhs) {
  Vec<T, L> result = lhs;
  result /= rhs;
  return result;
}

// Algorithm disptach

}
#endif