#pragma once

template <typename T> class Container {
public:
  Container(size_t max_x, size_t max_y)
      : _mx{max_x}, _my{max_y}, _data{new T[max_x * max_y]{}} {}
  T &operator[](size_t x, size_t y) {
    if (x >= _mx || y >= _my)
      throw std::runtime_error("角标越界");
    return _data[x * _my + y];
  }
  ~Container() { delete[] _data; }

private:
  size_t _mx;
  size_t _my;
  T *_data;
};
