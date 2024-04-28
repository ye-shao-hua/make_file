#pragma once

#include <cmath>
#include <iostream>
#include <point_in/point_concept.hpp>

// Point类
template <std::size_t Dim, typename NumberType = double> class Point {
public:
  using number_t = NumberType;
  using iterator_t = std::array<NumberType, Dim>::iterator;
  using const_iterator_t = std::array<NumberType, Dim>::const_iterator;
  [[nodiscard]] static consteval std::size_t dim() { return Dim; }

  constexpr Point() = default;
  constexpr Point(const Point &) = default;
  constexpr Point(Point &&) = default;
  constexpr Point &operator=(const Point &) = default;
  constexpr Point &operator=(Point &&) = default;
  constexpr Point(const auto &...arg) {
    static_assert(sizeof...(arg) == Dim || sizeof...(arg) == 0);
    int i = 0;
    ((m_data[i++] = arg), ...);
  }
  ~Point() = default;

  [[gnu::always_inline]] [[nodiscard]] constexpr Point
  operator+(const Point &other) const {
    Point result{};
    for (auto begin = this->begin(), other_begin = other.begin();
         auto &i : result)
      i = *begin++ + *other_begin++;
    return result;
  }

  [[gnu::always_inline]] constexpr Point &operator+=(const Point &other) {
    return *this = *this + other;
  }

  [[gnu::always_inline]] [[nodiscard]] constexpr Point
  operator/(std::size_t number) const {
    Point result{};
    for (auto begin = this->begin(); auto &i : result) {
      i = *begin++ / number;
    }
    return result;
  }

  [[gnu::always_inline]] constexpr Point &operator/=(std::size_t number) {
    return *this = *this / number;
  }

  [[gnu::always_inline]] [[nodiscard]] constexpr Point copy() const {
    return *this;
  }

  [[gnu::always_inline]] [[nodiscard]] constexpr Point *copy_ptr() const {
    return new Point{*this};
  }

  [[gnu::always_inline]] [[nodiscard]] constexpr bool
  operator<(const Point &other) const {
    return this->norm<2>() < other.norm<2>();
  }

  [[gnu::always_inline]] [[nodiscard]] constexpr bool
  operator==(const Point &other) const {
    for (auto i : std::ranges::iota_view{0uz, Dim})
      if (this->m_data[i] - other.m_data[i] > 1e-10) // not equal
        return false;
    return true;
  }

  [[gnu::always_inline]] [[nodiscard]] constexpr std::partial_ordering
  operator<=>(const Point &other) const = default;

  template <std::size_t N>
  [[gnu::always_inline]] [[nodiscard]] constexpr NumberType norm() const {
    static_assert(N > 0);

    if constexpr (Dim == 0)
      return NumberType{};

    NumberType num{};

    if constexpr (N <= 10) {
      for (auto i : std::ranges::iota_view(0uz, Dim))
        num += std::pow(m_data[i], N);
      return std::pow(num, 1. / N);
    }

    for (auto i : std::ranges::iota_view(0uz, Dim))
      if (m_data[i] > num)
        num = m_data[i];
    return num;
  }

  [[gnu::always_inline]] constexpr void show() const noexcept {
    for (auto i : m_data)
      std::cout << i << " ";
    std::cout << std::endl;
  }

  [[gnu::always_inline]] constexpr friend std::ostream &
  operator<<(std::ostream &os, const Point &self) {
    self.show();
    return os;
  }

  [[gnu::always_inline]] constexpr friend std::istream &
  operator>>(std::istream &is, Point &self) {
    for (auto &i : self.m_data)
      is >> i;
    return is;
  }

  NumberType &operator[](std::size_t index) {
    if (index >= Dim)
      std::cerr << "point::operator[]():index >= Dim\n";
    return m_data[index];
  }

  NumberType &x() {
    if (Dim < 1)
      std::cerr << "x():Dim < 1\n";
    return m_data[0];
  }

  NumberType &y() {
    if (Dim < 2)
      std::cerr << "y():Dim < 2\n";
    return m_data[1];
  }

  [[gnu::always_inline]] [[nodiscard]] constexpr iterator_t begin() noexcept {
    return m_data.begin();
  }

  [[gnu::always_inline]] [[nodiscard]] constexpr iterator_t end() noexcept {
    return m_data.end();
  }

  [[gnu::always_inline]] [[nodiscard]] constexpr const_iterator_t
  begin() const noexcept {
    return m_data.begin();
  }

  [[gnu::always_inline]] [[nodiscard]] constexpr const_iterator_t
  end() const noexcept {
    return m_data.end();
  }

  [[gnu::always_inline]] [[nodiscard]] constexpr std::array<NumberType, Dim> &
  data() noexcept {
    return m_data;
  }

private:
  std::array<NumberType, Dim> m_data{};
};
