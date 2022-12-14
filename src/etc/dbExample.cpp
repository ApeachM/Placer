///////////////////////////////////////////////////////////////////////////////
// Creator: Minjae Kim of CSDL, POSTECH
// Email:   kmj0824@postech.ac.kr
// GitHub:  ApeachM
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

#include "Circuit.h"
namespace Placer {
using namespace std;
void Circuit::dbTutorial() const {

  /*!
   * This function is example for using openDB API.
   *
   *
   * If you want not to use data structure which is implemented by TA
   * and want to use your own data structure,
   *
   * then you can know how to use OpenDB API referring below code.
   * */


  cout << endl << endl << endl << endl;
  cout << "OpenDB Tutorial starts." << endl;

  dbBlock *block = parser_.db_database_->getChip()->getBlock();
  dbSet<dbInst> db_instances = block->getInsts();

  // How to access all instances in database, and print the instance name
  int numOfInstance = 0;
  for (dbInst *db_instance : db_instances) {
    if (!db_instance->getName().empty())
      numOfInstance++;
  }
  cout << "The number of Instances: " << numOfInstance << endl;

  // Let's access only the first one instance, and explore some other methods.
  dbInst *db_inst = *db_instances.begin();
  cout << "The name of the instance: " << db_inst->getName() << endl;
  // As the library of the instance, we can know the library name, and cell width and height.
  dbMaster *lib = db_inst->getMaster();
  cout << "The name of the library of the instance: " << lib->getName() << endl;
  cout << "The width of the instance: " << db_inst->getMaster()->getWidth() << endl;
  cout << "The height of the instance: " << db_inst->getMaster()->getHeight() << endl << endl;

  cout << "The pin libraries of the instance" << endl;
  for (auto library_terminals : db_inst->getMaster()->getMTerms()) {
    cout << " ";
    cout << "Name: " << library_terminals->getName() << "\t";
    cout << "Signal Type: " << library_terminals->getSigType().getString() << "\t";
    cout << "Terminal Index: " << library_terminals->getIndex() << "\t";
    cout << endl;
  }
  cout << "The number of the terminals of instance: " << db_inst->getMaster()->getMTermCount() << endl;
  cout << endl;

  // instance location setting
  db_inst->setLocation(200, 300);

  cout << "The pin data" << endl;
  for (auto instance_terminal : db_inst->getITerms()) {
    cout << " ";
    cout << "Terminal Name: " << instance_terminal->getMTerm()->getName() << "\t";
    cout << "Signal Type: " << instance_terminal->getSigType().getString() << "\t";
    cout << "Terminal Index: " << instance_terminal->getMTerm()->getIndex() << endl;
    cout << "  Connected Net: ";
    if (instance_terminal->getNet() != nullptr) {
      cout << instance_terminal->getNet()->getName() << endl;
      if (instance_terminal->getNet()->getName() != "clk") {
        cout << "   connected Pins correspond to the net" << endl;
        for (auto terminals_in_net : instance_terminal->getNet()->getITerms()) {
          cout << "   "
               << terminals_in_net->getMTerm()->getName() << " in "
               << terminals_in_net->getInst()->getName() << "("
               << terminals_in_net->getInst()->getMaster()->getName() << ") instance" << endl;
        }
      }
    } else {
      cout << "None" << endl;
    }
  }

  // # 2. traverse nets
  for (int i = 0; i < 3; ++i) {
    cout << endl;
  }
  // access the nets in the circuit
  cout << "Signal Type\tIoType\tTerminal Name" << endl;
  for (auto net : block->getNets()) {
    for (auto terminal : net->getITerms()) {
    }
    for (auto terminal : net->getBTerms()) {
      cout << terminal->getSigType().getString() << "\t";
      cout << terminal->getIoType().getString() << "\t";
      cout << terminal->getName() << endl;
      for (auto bPin : terminal->getBPins()) {
        cout << " bPin ID: " << bPin->getId() << endl;
        for (auto box : bPin->getBoxes()) {
          cout << "  box xMin: " << box->xMin() << endl;
          cout << "  box xMax: " << box->xMax() << endl;
          cout << "  box DX: " << box->getDX() << endl;
          cout << "  box yMin: " << box->yMin() << endl;
          cout << "  box yMax: " << box->yMax() << endl;
          cout << "  box DY: " << box->getDY() << endl;
          cout << "  box width: " << box->getWidth() << endl;
          cout << "  box dir: " << box->getDir() << endl;
          if (box->getBlockVia())/* meaningless in this case*/
            cout << "  via name: " << box->getBlockVia()->getName() << endl;
        }

      }
    }
  }


  // # 3. Get Die information
  odb::Rect Die, Core;
  block->getDieArea(Die);
  block->getCoreArea(Core);
  cout << Die.dx() << " " << Die.dy() << endl;
  cout << Core.dx() << " " << Core.dy() << endl;

}

}