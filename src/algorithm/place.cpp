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
#include "matrixSolver.h"

namespace Placer {
void Circuit::placeExample() {
  /*!
   * This below code is example code for simple placement (random placement).
   * You should implement your placer referring below code.
   * After then, you should erase below simple placement code.
   * */

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

}


void Circuit::quadraticPlacement() {
  // matrix solve example.
  // You should refer below function when you get x respect to Ax = b
  // Below function is implemented in src/algorithm/math/matrixSolver.cpp
  solve_example();
}
void Circuit::myPlacement() {

}

}
