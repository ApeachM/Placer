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
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Circuit.h"

using namespace std;

void callUsage() {
  cout << "Usage:" << endl;
  cout << "\t./evaluator <defFileName.def> 0||1" << endl << endl;
  cout << "\tYou should get the argument as the def file name in test/benchmarks," << endl;
  cout << "\tand write zero or one evaluate the density or not." << endl;
  cout << "\tIf you want to evaluate only for quadratic, then put zero in there. " << endl << endl;

  cout << "\tEx)" << endl;
  cout << "\t\t./evaluator simple01.def 0" << endl;
}

int main(int argc, char **argv) {

  if (argc != 3) {
    callUsage();
    return 0;
  }
  string lefName = "Nangate45.lef";
  // string defName = "simple01.def"
  string defName;
  {  // simple argument parsing
    stringstream ss;
    ss << argv[1];
    ss >> defName;
  }

  bool density_evaluate = false;
  {  // simple argument parsing
    string argv2;
    stringstream ss;
    ss << argv[2];
    ss >> argv2;
    if (argv2 == "0")
      density_evaluate = false;
    else if (argv2 == "1")
      density_evaluate = true;
    else {
      callUsage();
      return 0;
    }
  }

  string test_path_name = "../test/benchmarks/";
  string output_path_name = "../output/placer/";

  Placer::Circuit circuit_input;
  circuit_input.parse(test_path_name + lefName, test_path_name + defName);
  // Reference circuit is parsed.

  Placer::Circuit circuit_output;
  circuit_output.parse(test_path_name + lefName, output_path_name + defName);
  // Circuit made by you is parsed.

  // HPWL calculation
  cout << scientific << endl;
  cout << "HPWL: " << static_cast<double>(circuit_output.getHPWL()) << endl;

  // evaluation execute
  if (!density_evaluate) {
    // for quadratic evaluation || basic evaluation
    if (!circuit_output.evaluate(&circuit_input)) {
      // fail
      cout << "Some condition is not satisfied." << endl;
      return 0;
    }
  } else {
    // for evaluation with density checking
    if (!circuit_output.evaluateIncludeDensity(&circuit_input)) {
      cout << "Some condition is not satisfied." << endl;
      return 0;
    }
  }

  cout << "Evaluation is end completely." << endl;
  return 0;
}