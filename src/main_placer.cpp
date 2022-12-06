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
void callUsage() {
  cout << "Usage:" << endl;
  cout << "\t./placer <benchNumber>" << endl;
  cout << "Ex)" << endl;
  cout << "\t\t./placer 1" << endl;
}

int main(int argc, char **argv) {

  if (argc != 2) {
    callUsage();
    return 0;
  }

  string benchNumber;
  {
    stringstream ss;
    ss << argv[1];
    ss >> benchNumber;
  }
  string lefName = "test" + benchNumber + ".input.lef";
  string defName = "test" + benchNumber + ".input.def";
  string test_path_name = "../test/competition/";
  string output_path_name = "../output/placer/";

  // Parsing and initialize start
  Placer::Circuit circuit;
  circuit.parse(test_path_name + lefName, test_path_name + defName);
  circuit.analyzeBench();

  // Your own placement
  circuit.myPlacement();

  // save image
  string img_file_name = "result" + benchNumber;
  circuit.saveImg(img_file_name);
  circuit.write(output_path_name + defName);

  cout << "Def is written successfully." << endl;
}

