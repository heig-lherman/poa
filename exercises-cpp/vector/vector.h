#pragma once

#include <algorithm>

class Vector {

private:
  size_t m_size;
  int *m_data;

public:
  Vector() : m_size{0}, m_data{nullptr} {}

  Vector(size_t size) : m_size{size}, m_data{new int[size]} {}

  Vector(const Vector &other)
      : m_size{other.m_size}, m_data{new int[other.m_size]} {

    for (size_t i = 0; i < m_size; ++i) {
      m_data[i] = other.m_data[i];
    }
  }

  ~Vector() { delete[] m_data; }

  Vector &operator=(const Vector &other) {
    if (this != &other) {
      delete[] m_data;
      m_size = other.m_size;
      m_data = new int[other.m_size];
      for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
      }
    }
    return *this;
  }

  [[nodiscard]] constexpr size_t size() const { return m_size; }

  int &operator[](size_t index) { return m_data[index]; }
};
