#include <iostream>
#include "Circuit.h"

using namespace std;

int main() {
  string lefName = "Nangate45.lef";
//  string defName = "large01.def";
  string defName = "simple01.def";
  string test_path_name = "../test/benchmarks/";
  string output_path_name = "../output/";

  Placer::Circuit circuit;
  circuit.parse(test_path_name + lefName, test_path_name + defName);

  // 1. Quadratic placement
  circuit.quadraticPlacement();
  circuit.write(output_path_name + "output_Quadratic_" + defName);

  // 2. Your own placement
  circuit.myPlacement();
  circuit.write(output_path_name + "output_myPlacement_" + defName);

}