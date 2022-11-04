/*
University of Illinois/NCSA Open Source License

Copyright (c) 2013 University of Illinois at Urbana-Champaign. All rights
reserved.

Developed by:

The teaching staff of VLSI CAD: Logic to Layout

    University of Illinois

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal with
    the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
    the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

* Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimers.

* Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimers in the documentation
and/or other materials provided with the distribution.

* Neither the names of the CodingSpectator Team, University of Illinois, nor the
names of its contributors may be used to endorse or promote products derived
    from this Software without specific prior written permission.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
    FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE CONTRIBUTORS
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS WITH THE SOFTWARE.
*/
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
