///////////////////////////////////////////////////////////////////////////////
// This is property of CSDL, POSTECH in Korea
// Creator: Minjae Kim of CSDL, POSTECH
// Email:   kmj0824@postech.ac.kr
// GitHub:  ApeachM
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
#include "Circuit.h"

using namespace std;

int main(int argc, char **argv) {

  if (argc != 2) {
    cout << "Usage:" << endl;
    cout << "\t./qPlacer <defFileName.def>" << endl << endl;
    cout << "\tYou should get the argument as the def file name in test/benchmarks." << endl << endl;

    cout << "\tEx)" << endl;
    cout << "\t\t./qPlacer simple01.def" << endl;
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

  string test_path_name = "../test/benchmarks/";
  string output_path_name = "../output/qPlacer/";

  Placer::Circuit circuit;
  circuit.parse(test_path_name + lefName, test_path_name + defName);

   circuit.howToUse();

  circuit.quadraticPlacement();
  circuit.write(output_path_name + defName);

  cout << "Def is written successfully." << endl;

}