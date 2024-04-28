#pragma once
#include <fstream>
#include <mesh/Container.hpp>
#include <vec_in/CellVec.hpp>
#include <vec_in/CellVecAdd.hpp>

class mesh {
  // make the array and fill it by data of txt file
public:
  // transfer data to mesh from txtRead class.
  void set_master(cell ce) { master = ce; }
  void set_mental(CellVec Ce) { mental = Ce; }
  void set_die(CellVecAdd Ce) { die = Ce; }

  void show() {
    master.show();
    mental.show();
    die.show();
  }

  // Norm function is used to get First-order norm.
  std::size_t Norm(Point<2, double> point) {
    std::size_t a, b;
    a = (*point.begin() + 1) / 0.002;
    b = *(point.begin() + 1) / 0.002;
    return a + b;
  }
  // get the Point<2,double> in a cell which in up-right place
  Point<2, double> maxNormPoint(cell ce) {
    std::size_t norm = 0;
    std::size_t n = 0;
    std::size_t a;
    for (auto i = 0; i < ce.get_number(); i++) {
      a = Norm(*(ce.begin() + i));
      if (a > norm) {
        norm = a;
        n = i;
      }
    }
    return *(ce.begin() + n);
  }
  Point<2, double> minNormPoint(cell ce) {
    std::size_t norm = 999;
    std::size_t n = 0;
    std::size_t a;
    for (auto i = 0; i < ce.get_number(); i++) {
      a = Norm(*(ce.begin() + i));
      if (a < norm) {
        norm = a;
        n = i;
      }
    }
    return *(ce.begin() + n);
  }
  // get the index of a point
  std::size_t geta(Point<2, double> point) {
    return (*point.begin() + 1) / 0.002;
  }
  std::size_t getb(Point<2, double> point) {
    return *(point.begin() + 1) / 0.002;
  }

  // add master into space
  void MasterAdd() {
    static constexpr int maxe = 9;
    Point<2, double> point{};
    std::size_t maxa, maxb, mina, minb;
    point = maxNormPoint(master);
    maxa = geta(point);
    maxb = getb(point);
    point = minNormPoint(master);
    mina = geta(point);
    minb = getb(point);
    for (auto i = mina; i < maxa; i++)
      for (auto j = minb; j < maxb; j++) {
        space[i, j] = maxe;
      }
  }

  void MentalAdd() {
    Point<2, double> point{};
    static constexpr int maxe = 9;
    std::size_t maxa, maxb, mina, minb;
    for (auto k : mental) {
      point = maxNormPoint(k);
      maxa = geta(point);
      maxb = getb(point);
      point = minNormPoint(k);
      mina = geta(point);
      minb = getb(point);
      for (auto i = mina; i < maxa; i++)
        for (auto j = minb; j < maxb; j++) {
          space[i, j] = maxe;
        }
    }
  }
  void DieAdd() {
    Point<2, double> point{};
    std::size_t maxa, maxb, mina, minb;
    for (auto k : die) {
      point = maxNormPoint(k);
      maxa = geta(point);
      maxb = getb(point);
      point = minNormPoint(k);
      mina = geta(point);
      minb = getb(point);
      for (auto i = mina; i < maxa; i++)
        for (auto j = minb; j < maxb; j++) {
          space[i, j] = k.get_value();
        }
    }
  }

  std::size_t find(Point<2, double> point) {
    std::size_t a, b;
    a = geta(point);
    b = getb(point);
    return space[a, b];
  }

  void savecsv(std::string s) {
    std::ofstream csvfile;
    csvfile.open(s, std::ios::out);
    for (auto i = 0; i < 2000; i++) {
      for (auto j = 0; j < 5500; j++) {
        csvfile << space[i, j] << ",";
      }
      csvfile << std::endl;
    }
  }

  void test(std::string s) {
    MasterAdd();
    MentalAdd();
    DieAdd();
    std::size_t tst = 0;
    Point<2, double> p{-0.117, 0.27};
    tst = find(p);
    std::cout << tst;

    savecsv(s);
  }

private:
  cell master{};
  CellVec mental{};
  CellVecAdd die{};
  Container<short> space{2000, 5500};
};
