/*!
 * Write **your own** code.
 * !!! Cheating will be strictly not accepted. !!!
 * If cheating is detected by the similarity check program and TA determine that you have cheated,
 * then you will get F grade or zero point for this term project.
 * You can use external libraries for only pure math libraries; i.e) fft, sparse matrix, etc
 * If you want to use external library, then please check whether it is okay by contact to TA.
 * */

#include <random>
#include "Circuit.h"
#include "solver.h"

namespace Placer {
void Circuit::place() {
  /*!
   * This below code is example code for simple placement (random placement).
   * You should implement your placer referring below code.
   * After then, you should erase below simple placement code.
   * */

  /*
  // random place
  // this is simple place example
  //    mt19937 genX(1111);  // fix seed
  //    mt19937 genY(2222);  // fix seed
  mt19937 genX(random_device{}());
  mt19937 genY(random_device{}());
  uniform_int_distribution<int> disX(0, (int) die_->getWidth());
  uniform_int_distribution<int> disY(0, (int) die_->getHeight());

  for (Instance *instance : instance_pointers_) {
    instance->setCoordinate(disX(genX), disY(genY));
  }

  cout << "RandomPlace Done." << endl;

  */

}

// write the matrix directly in code
void solve_example() {
  cout << endl << "** small demonstration **" << endl;
  coo_matrix A;
  int row_idx[] = {0, 0, 1, 1, 1, 2, 2};
  int col_idx[] = {0, 1, 0, 1, 2, 1, 2};
  double data[] = {4.0, -1.0, -1.0, 4.0, -1.0, -1.0, 4.0};
  // component # excepting zero value
  int data_number = sizeof(row_idx) / sizeof(int);

  // initializing coo_matrix object
  A.n = 3;  // 3x3 matrix
  A.nnz = data_number;
  A.row.resize(data_number);
  A.col.resize(data_number);
  A.dat.resize(data_number);

  // value inserting in coo_matrix object
  A.row = valarray<int>(row_idx, A.nnz);
  A.col = valarray<int>(col_idx, A.nnz);
  A.dat = valarray<double>(data, A.nnz);

  // initialize as [1, 1, 1] for golden solution
  valarray<double> x(1.0, A.n);
  valarray<double> b(A.n);
  A.matvec(x, b); // b = Ax

  cout << "b should equal [3,2,3]" << endl;
  cout << "b = ";
  print_valarray(b);

  // make we don't know the x value
  for (int i = 0; i < A.n; ++i) {
    x[i] = (double) random() / (double) RAND_MAX;
  }

  // solve for x
  cout << endl << "x = ";
  print_valarray(x);
  A.solve(b, x);
  cout << "after solve" << endl;
  cout << "x = ";
  print_valarray(x);
}

void Circuit::quadraticPlacement() {
  solve_example();
}
void Circuit::myPlacement() {

}

}
