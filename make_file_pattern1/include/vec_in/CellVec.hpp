#pragma once
#include <cell_in/cell.hpp>
#include <vector>

class CellVec {
  // CellVec class ,a component by Cell
public:
  CellVec() = default;
  void set_number(std::size_t number) { m_number = number; }
  std::size_t get_number() { return m_number; }
  CellVec &operator+=(cell cell) {
    this->m_data.push_back(cell);
    return *this;
  }
  CellVec &operator=(const CellVec &Ce) = default;
  cell &operator[](std::size_t index) {
    if (index >= m_data.size())
      std::cerr << "cellvec::operator[](): index >= m_data.size()\n"
                << index << " >= " << m_data.size() << "\n";
    return m_data[index];
  }
  std::vector<cell>::iterator begin() { return m_data.begin(); }
  std::vector<cell>::iterator end() { return m_data.end(); }
  void show() {
    std::cout << m_number << std::endl;
    for (auto i : m_data) {
      i.show();
      std::cout << std::endl;
    }
  }
  std::vector<cell> &data() { return m_data; }

protected:
  std::vector<cell> m_data{};
  std::size_t m_number{};
};
