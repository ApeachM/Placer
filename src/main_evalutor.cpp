///////////////////////////////////////////////////////////////////////////////
// This is property of CSDL, POSTECH in Korea
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
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Evaluator.h"

using namespace std;

void callUsage() {
  cout << "Usage:" << endl;
  cout << "\tFor quadratic placer," << endl;
  cout << "\t\t./evaluator <defFileName.def>  0" << endl;
  cout << "\t\tEx) For quadratic," << endl;
  cout << "\t\t\t./evaluator simple01.def 0" << endl << endl;
  cout << "\t\t\t./evaluator medium01.def 0" << endl << endl;

  cout << "\tFor general placer," << endl;
  cout << "\t\t./evaluator <benchNumber>  1" << endl;
  cout << "\t\tEx) For GeneralPlacer," << endl;
  cout << "\t\t\t./evaluator 1 1" << endl;
  cout << "\t\t\t./evaluator 4 1" << endl;
}

int main(int argc, char **argv) {

  if (argc != 3) {
    callUsage();
    return 0;
  }
  string lefName;
  string defName;
  {
    stringstream ss;
    ss << argv[1];
    ss >> defName;
  }

  bool general_place_evaluate;
  {
    string argv2;
    stringstream ss;
    ss << argv[2];
    ss >> argv2;
    if (argv2 == "0")
      general_place_evaluate = false;
    else if (argv2 == "1")
      general_place_evaluate = true;
    else {
      callUsage();
      return 0;
    }
  }

  string test_path_name;
  string output_path_name;
  if (!general_place_evaluate) {
    lefName = "Nangate45.lef";
    test_path_name = "../test/benchmarks/";
    output_path_name = "../output/placer/";
  } else {
    string benchNumber = defName;
    lefName = "test" + benchNumber + ".input.lef";
    defName = "test" + benchNumber + ".input.def";
    test_path_name = "../test/competition/test" + benchNumber + "/";
    output_path_name = "../output/placer/";
  }

  Placer::Evaluator circuit_input;
  circuit_input.parse(test_path_name + lefName, test_path_name + defName);
  // Reference circuit is parsed.

  Placer::Evaluator circuit_output;
  circuit_output.parse(test_path_name + lefName, output_path_name + defName);
  // Circuit made by you is parsed.

  // HPWL calculation
  cout << scientific << endl;
  cout << "HPWL: " << static_cast<double>(circuit_output.getHPWL()) << endl;

  // evaluation execute
  if (!general_place_evaluate) {
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