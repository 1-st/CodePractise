#include <DC/defer.hpp>
#include <DC/macro/file.hpp>
#include <DC/utils/Table.hpp>
#include <DC/utils/type.hpp>
#include <iomanip>
#include <iostream>
#include <vector>
// 矩阵链乘法
// 给定一个n个矩阵的阵列,求出最适合矩阵的一个括号化
// <A1,A2,A3,...,An>
// size of An:p[n-1]*p[n]
// c:cost
// d:division

//继承Table,添加我们需要的方法
struct A : public Table<int> {
  int *p;
  uint64 p_size;
  //按p数组初始化
  A(std::vector<int> &v_p)
      : Table(v_p.size() - 1, v_p.size() - 1), p_size(v_p.size()) {
    this->p = new int[p_size];
    for (uint64 i = 0; i < p_size; i++) {
      this->p[i] = v_p[i];
    }
  }
  void calculate() {
    for (uint64 i = 0; i < this->p_size - 1; i++) {
      arr[i][i] = 0;
    }
    for (uint64 len = 2; len <= X; len++) {
      for (uint64 l = 0; l < X - len + 1; l++) { // left
        uint64 r = l + len - 1;                  // right
        arr[l][r] = INT_MAX;
        for (uint64 d = l; d < r; d++) {
          int q = arr[l][d] + arr[d + 1][r] + p[l] * p[d + 1] * p[r + 1];
          if (q < arr[l][r]) {
            arr[l][r] = q;
            arr[r][l] = d; //反向存储分割数组,节约越一半数组空间
          }
        }
      }
    }
  }
  void print(std::ofstream &out) {
    out << "arr:" << std::endl;
    for (size_t i = 0; i < X; i++) {
      for (size_t j = 0; j < Y; j++) {
        out << std::setiosflags(std::ios::left) << std::setw(8) << arr[i][j];
      }
      out << std::endl;
    }
    out << "cost:" << std::endl;
    for (uint64 i = 0; i < X; i++) {
      for (uint64 j = 0; j < Y; j++) {
        if (j < i) {
          out << std::setiosflags(std::ios::left) << std::setw(8) << " ";
          continue;
        }
        out << std::setiosflags(std::ios::left) << std::setw(8) << arr[i][j];
      }
      out << std::endl;
    }
    out << "divition:" << std::endl;
    for (uint64 i = 1; i < X; i++) {
      for (uint64 j = 1; j < X; j++) {
        if (j < i) {
          out << std::setiosflags(std::ios::left) << std::setw(8) << " ";
          continue;
        }
        out << std::setiosflags(std::ios::left) << std::setw(8) << arr[j][i];
      }
      out << std::endl;
    }
  }
  ~A() { delete[] p; }
};

int main() {
  F_IO;
  std::vector<int> p{};
  int buf;
  while (true) {
    in >> buf;
    if (in.eof())
      break;
    p.push_back(buf);
  }
  A m(p);
  m.setValueAll(0);
  m.calculate();
  m.print(out);
  return 0;
}
