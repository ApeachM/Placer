/*!
 * Write **your own** code.
 * !!! Cheating will be strictly not accepted. !!!
 * If cheating is detected by the similarity check program and TA determine that you have cheated,
 * then you will get F grade or zero point for this term project.
 * You can use external libraries for only pure math libraries; i.e) fft, sparse matrix, etc
 * If you want to use external library, then please check whether it is okay by contact to TA.
 * */

#include "Circuit.h"
#include "matrixSolver.h"

namespace Placer {


void Circuit::quadraticPlacement() {
  // matrix solve example.
  // You should refer below function when you get x respect to Ax = b
  // Below function is implemented in src/algorithm/math/matrixSolver.cpp
  solve_example();
}
void Circuit::myPlacement() {
  this->placeExample();
}

}
