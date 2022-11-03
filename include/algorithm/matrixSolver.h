#ifndef SOLVER_H_
#define SOLVER_H_

#include <cstdio>
#include <cstdlib>
#include <valarray>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

class coo_matrix {
  // COOrdinate sparse matrix
 public:
  int n;
  int nnz;
  valarray<int> row;
  valarray<int> col;
  valarray<double> dat;

  void matvec(const valarray<double> &x, valarray<double> &y);
  void solve(const valarray<double> &b, valarray<double> &x);
};

template<typename T>
void print_valarray(valarray<T> &v) {
  for (size_t i = 0; i < v.size(); ++i) {
    cout << v[i] << " ";
  }
  cout << endl;
}

void solve_example();

#endif
