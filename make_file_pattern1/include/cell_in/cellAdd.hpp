#pragma once
#include <cell_in/cell.hpp>

class cellAdd : public cell {
  // cellAdd class,have an additional property 'm_value' to record epsilon(e)
public:
  void show() {
    std::cout << m_name << std::endl;
    std::cout << m_PointNumber << std::endl;
    for (auto i : m_data) {
      i.show();
      std::cout << std::endl;
    }
    std::cout << m_value << std::endl;
  }
  void add_value(double va) { m_value = va; }
  double get_value() { return m_value; }

private:
  double m_value{};
};
