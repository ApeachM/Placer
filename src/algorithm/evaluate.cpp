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
#include <utility>
#include <algorithm>
#include "Circuit.h"

namespace Placer {
bool Circuit::evaluate(Circuit *compared_circuit) {
  compared_circuit_ = compared_circuit;

  // Variable numbers check
  vector<int> variable_numbers = compared_circuit_->getVariableNumbers();
  if (!cellNumCheck(variable_numbers.at(0))) {
    cout << "Cell number is different with inputted file." << endl;
    return false;
  } else if (!netNumCheck(variable_numbers.at(1))) {
    cout << "Net number is different with inputted file." << endl;
    return false;
  } else if (!pinNumCheck(variable_numbers.at(2))) {
    cout << "Pin number is different with inputted file." << endl;
    return false;
  } else if (!padNumCheck(variable_numbers.at(3))) {
    cout << "Pad number is different with inputted file." << endl;
    return false;
  }

  // Placed check
  if (!placeCheck()) {
    cout << "Some cell is not placed." << endl;
    return false;
  }

  // Density check
  if (!densityCheck()) {
    cout << "This circuit doesn't pass density threshold." << endl;
    return false;
  }

  return true;
}
vector<int> Circuit::getVariableNumbers() {
  vector<int> varNums;
  varNums.push_back(getCellNumber());
  varNums.push_back(getNetNumber());
  varNums.push_back(getPinNumber());
  varNums.push_back(getPadNumber());
  return varNums;
}
int Circuit::getCellNumber() {
  if ((int) instance_pointers_.size() < 0)
    assert(0);
  return (int) instance_pointers_.size();
}
int Circuit::getNetNumber() {
  if ((int) net_pointers_.size() < 0)
    assert(0);
  return (int) net_pointers_.size();
}
int Circuit::getPinNumber() {
  if ((int) pin_pointers_.size() < 0)
    assert(0);
  return (int) pin_pointers_.size();
}
int Circuit::getPadNumber() {
  if ((int) pad_pointers_.size() < 0)
    assert(0);
  return (int) pad_pointers_.size();
}
bool Circuit::cellNumCheck(int ref_cell_num) {
  if (ref_cell_num == instance_pointers_.size())
    return true;
  else
    return false;
}
bool Circuit::netNumCheck(int ref_net_num) {
  if (ref_net_num == net_pointers_.size())
    return true;
  else
    return false;
}
bool Circuit::pinNumCheck(int ref_pin_num) {
  if (ref_pin_num == pin_pointers_.size())
    return true;
  else
    return false;
}
bool Circuit::padNumCheck(int ref_pad_num) {
  if (ref_pad_num == pad_pointers_.size())
    return true;
  else
    return false;
}
bool Circuit::placeCheck() {
  bool all_placed = true;
  for (Instance *instance : instance_pointers_)
    if (!instance->isPlaced())
      all_placed = false;
  return all_placed;
}
bool Circuit::densityCheck() {
  // make the grid as 40x40
  int number_of_grid_X = 40;
  int number_of_grid_Y = 40;
  uint die_width = die_->getWidth();
  uint die_height = die_->getHeight();
  int bin_width = static_cast<int>(die_width / number_of_grid_X);
  int bin_height = static_cast<int>(die_height / number_of_grid_Y);

  struct Bin {
    Bin() = default;;
    explicit Bin(int area, pair<int, int> lower_left, pair<int, int> upper_right)
        : area(area), lower_left(std::move(lower_left)), upper_right(std::move(upper_right)) {}
    vector<Instance *> instances;
    pair<int, int> lower_left;
    pair<int, int> upper_right;
    int area{};
    int cell_area{};
  };
  vector<vector<Bin>> bins2D;
  for (int i = 0; i < number_of_grid_Y; ++i) {
    vector<Bin> bins1D;
    for (int j = 0; j < number_of_grid_X; ++j) {
      pair<int, int> lower_left{i * bin_width, j * bin_height};
      pair<int, int> upper_right{(i + 1) * bin_width, (j + 1) * bin_height};
      bins1D.emplace_back(static_cast<int>(die_width * die_height), lower_left, upper_right);
    }
    bins2D.push_back(bins1D);
  }

  for (Instance *instance : instance_pointers_) {
    if (instance->isPlaced()) {
      int position_x = instance->getCoordinate().first;
      int position_y = instance->getCoordinate().second;
      int bin_coordinate_x = floor(position_x / bin_width);
      int bin_coordinate_y = floor(position_y / bin_height);
      if (bin_coordinate_x >= number_of_grid_X)
        bin_coordinate_x = number_of_grid_X - 1;
      if (bin_coordinate_y >= number_of_grid_Y)
        bin_coordinate_y = number_of_grid_Y - 1;
      bins2D.at(bin_coordinate_x).at(bin_coordinate_y).instances.push_back(instance);
      bins2D.at(bin_coordinate_x).at(bin_coordinate_y).cell_area += static_cast<int>(instance->getArea());

    }
  }

  // find bin which has max density
  // time complexity: O(mxm), m is bin numbers
  int max_cell_area_in_bin = 0;
  Bin max_density_bin;
  for (int i = 0; i < number_of_grid_Y; ++i) {
    for (int j = 0; j < number_of_grid_X; ++j) {
      if (max_cell_area_in_bin < bins2D.at(j).at(i).cell_area) {
        max_density_bin = bins2D.at(j).at(i);
        max_cell_area_in_bin = max_density_bin.cell_area;
      }
    }
  }

  auto max_density =
      static_cast<float>(max_cell_area_in_bin * 1e-10) / static_cast<float>(1e-10 * bin_height * bin_width);

  if (max_density > 1.2) {
    cout << "The overflow grid is ("
         << max_density_bin.lower_left.first << ", " << max_density_bin.lower_left.second << ")"
         << ", (" << max_density_bin.upper_right.first << ", " << max_density_bin.upper_right.second << ")"
         << "  (lower left), (upper right)" << endl;
    cout << "Max density: " << max_density << endl;
    return false;
  } else {
    return true;
  }
}
ulong Circuit::getHPWL() {
  ulong HPWL = 0;
  for (Net *net : net_pointers_) {
    HPWL += net->getHPWL();
  }
  return HPWL;
}

}