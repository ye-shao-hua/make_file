#pragma once
#include <cell_in/cellAdd.hpp>
#include <vec_in/CellVec.hpp>
// #include <vec_in/CellVec.hpp>

class CellVecAdd : public CellVec {
  // like CellVec,but replace cell by cellAdd
public:
  CellVecAdd &operator+=(cellAdd cell) {
    this->m_data.push_back(cell);
    return *this;
  }
  void show() {
    std::cout << m_number << std::endl;
    for (auto i : m_data) {
      i.show();
      std::cout << std::endl;
    }
  }
  cellAdd &operator[](std::size_t index) {
    if (index >= m_data.size())
      std::cerr << "cellAdd::operator[](): index >= m_data.size()\n"
                << index << " >= " << m_data.size() << "\n";
    return m_data[index];
  }
  std::vector<cellAdd>::iterator begin() { return m_data.begin(); }
  std::vector<cellAdd>::iterator end() { return m_data.end(); }
  CellVecAdd &operator=(const CellVecAdd &Ce) = default;
  std::vector<cellAdd> &data() { return m_data; }

private:
  std::vector<cellAdd> m_data{};
};
