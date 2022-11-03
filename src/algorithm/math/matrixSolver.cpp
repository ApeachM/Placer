#include "matrixSolver.h"

void solve_example() {
  // matrix solve example
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

double dot(const valarray<double> &x, const valarray<double> &y) {
  return (x * y).sum();
}

void coo_matrix::matvec(const valarray<double> &x, valarray<double> &y) {
  y = 0.0; // need to reset to 0 first.
  for (int i = 0; i < nnz; ++i) {
    y[row[i]] += dat[i] * x[col[i]];
  }
}

void coo_matrix::solve(const valarray<double> &b, valarray<double> &x) {
  // x = A^{-1} b with CG
  // https://en.wikipedia.org/wiki/Conjugate_gradient#Example_code_in_Matlab

  int maxit = 10000;
  valarray<double> Ax(n);
  valarray<double> Ap(n);
  valarray<double> r(n);
  valarray<double> p(n);
  double rnormold, alpha, rnorm;
//  double error, errorold = 1.0;

  for (size_t i = 0; i < x.size(); ++i) {
    x[i] = (double) random() / (double) RAND_MAX;
  }

  matvec(x, Ax);
  r = b - Ax;
  p = r;
  rnormold = dot(r, r);

  int i;
  for (i = 0; i < maxit; ++i) {
    matvec(p, Ap);
    alpha = rnormold / dot(p, Ap);

    // p *= alpha;
    x += alpha * p;

    // Ap *= alpha;
    r -= alpha * Ap;

    rnorm = dot(r, r);
    if (sqrt(rnorm) < 1e-8) { break; }
//    else {
//      error = abs(dot(r, x));
//      errorold = error;
//    }

    p *= (rnorm / rnormold);
    p += r;

    rnormold = rnorm;
  }

  if (i == maxit)
    cerr << "Warning: reaches maximum iteration." << endl;
}