///////////////////////////////////////////////////////////////////////////////
// This is property of CSDL, POSTECH in Korea
//
// BSD 3-Clause License
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
///////////////////////////////////////////////////////////////////////////////
#include <random>
#include "Circuit.h"

namespace Placer {

void Circuit::placeExample() {
  /*!
   * This below code is example code for simple placement (random placement).
   * You should implement your placer referring below code in `src/algorithm/place.cpp`.
   * */

  // Random place
  // This is simple place example

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

void Circuit::howToUse() {
  /*!
   * This function is
   * example for how to use variables in Circuit class
   *
   * You should refer this function and know how to use `Net`, `Instance`, `Pin`, etc variables
   * */

  for (int i = 0; i < 5; ++i) cout << endl;

  // Access all Instances(cells) in the circuit
  cout << "Access all Instances(cells) in the circuit" << endl;
  for (Instance *instance : instance_pointers_) {
    string cell_name = instance->getName();
    cout << cell_name << " ";
  }
  cout << endl << endl;

  // Access the 5th instance for demonstrate how to use the data structures
  cout << "Access 5th cell in the circuit." << endl;
  Instance *instance = instance_pointers_.at(10);
  cout << "Cell name: " << instance->getName() << endl;
  cout << "Cell height: " << instance->getHeight() << endl;
  cout << "Cell width: " << instance->getWidth() << endl;
  cout << "Cell area: " << instance->getArea() << endl;
  cout << "Cell library name: " << instance->getLibName() << endl;
  cout << "Cell coordinate before set coordinate: " << endl << "  "
       << "x[" << instance->getCoordinate().first << "] "
       << "y[" << instance->getCoordinate().second << "]" << endl;
  // set coordinate of the cell as (100, 200)
  instance->setCoordinate(100, 200);
  cout << "Cell coordinate after set coordinate: " << endl << "  "
       << "x[" << instance->getCoordinate().first << "] "
       << "y[" << instance->getCoordinate().second << "]" << endl;

  // Access pins in that instance
  cout << "Access pins in that instance" << endl;
  for (Pin *pin : instance->getPins()) {
    cout << "\tPin coordinate: "
         << "x[" << pin->getCoordinate().first << "] "
         << "y[" << pin->getCoordinate().second << "]";
    cout << "\t\tCorrespond instance name: " << pin->getInstance()->getName();
    cout << "\t\tSignal Type: " << pin->getSignalType();
    cout << "\t\tPin name:" << pin->getPinName() << endl;
  }


  // Grab any pin for demonstrate how to use the data structures
  // here, I'll grab 2nd pin in the above selected cell
  if (instance->getPins().at(2)) {
    Pin *pin = instance->getPins().at(2);

    // You can access the instance correspond to the pin
    cout << "The name of instance which includes the pin: " << pin->getInstance()->getName() << endl << endl;
    // You can access the net correspond to the pin
    Net *net = pin->getNet();
    cout << "Net name: " << net->getName() << endl;
    // You can access the pins which is included in the net
    for (Pin *connected_pin : net->getConnectedPins()) {
      cout << "\tPin coordinate: "
           << "x[" << connected_pin->getCoordinate().first << "] "
           << "y[" << connected_pin->getCoordinate().second << "]";
      if (connected_pin->getInstance())
        cout << "\t\tCorrespond instance name: " << connected_pin->getInstance()->getName();
      cout << "\t\tSignal Type: " << connected_pin->getSignalType();
      cout << "\t\tPin name:" << connected_pin->getPinName() << endl;

    }
  }

}
}
