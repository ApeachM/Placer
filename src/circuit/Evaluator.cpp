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
#include "Evaluator.h"
namespace Placer {
bool Evaluator::placeLegalityCheck(Evaluator *compared_circuit) {
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
  if (!isAllCellInDie()) {
    cout << "Some cell is out of the die." << endl;
    return false;
  }
  return true;
}
bool Evaluator::evaluate(Evaluator *compared_circuit) {
  if (!placeLegalityCheck(compared_circuit))
    return false;

  // Density check
  if (!densityCheck()) {
    cout << "This circuit doesn't pass density threshold." << endl;
    return false;
  }

  return true;
}
vector<int> Evaluator::getVariableNumbers() {
  vector<int> varNums;
  varNums.push_back(getCellNumber());
  varNums.push_back(getNetNumber());
  varNums.push_back(getPinNumber());
  varNums.push_back(getPadNumber());
  return varNums;
}
int Evaluator::getCellNumber() {
  if ((int) instance_pointers_.size() < 0)
    assert(0);
  return (int) instance_pointers_.size();
}
int Evaluator::getNetNumber() {
  if ((int) net_pointers_.size() < 0)
    assert(0);
  return (int) net_pointers_.size();
}
int Evaluator::getPinNumber() {
  if ((int) pin_pointers_.size() < 0)
    assert(0);
  return (int) pin_pointers_.size();
}
int Evaluator::getPadNumber() {
  if ((int) pad_pointers_.size() < 0)
    assert(0);
  return (int) pad_pointers_.size();
}
bool Evaluator::cellNumCheck(int ref_cell_num) {
  if (ref_cell_num == instance_pointers_.size())
    return true;
  else
    return false;
}
bool Evaluator::netNumCheck(int ref_net_num) {
  if (ref_net_num == net_pointers_.size())
    return true;
  else
    return false;
}
bool Evaluator::pinNumCheck(int ref_pin_num) {
  if (ref_pin_num == pin_pointers_.size())
    return true;
  else
    return false;
}
bool Evaluator::padNumCheck(int ref_pad_num) {
  if (ref_pad_num == pad_pointers_.size())
    return true;
  else
    return false;
}
bool Evaluator::placeCheck() {
  bool all_placed = true;
  for (Instance *instance : instance_pointers_)
    if (!instance->isPlaced())
      all_placed = false;
  return all_placed;
}
bool Evaluator::isAllCellInDie() {
  ulong die_width = die_->getWidth();
  ulong die_height = die_->getHeight();
  for (Instance *instance : instance_pointers_) {
    pair<int, int> coordinate = instance->getCoordinate();
    if (coordinate.first < 0 || coordinate.first > die_width)
      return false;
    else if (coordinate.second < 0 || coordinate.second > die_height)
      return false;
  }
  return true;
}
pair<int, int> Evaluator::getBinNumbers() {
  // get the average cell width and height
  long averageWidth = 0, averageHeight = 0;
  for (Instance *instance : instance_pointers_) {
    averageWidth += instance->getWidth();
    averageHeight += instance->getHeight();
  }
  if (averageWidth < 0)
    assert(0);
  averageWidth /= static_cast<int>(instance_pointers_.size());
  averageHeight /= static_cast<int>(instance_pointers_.size());

  int number_of_grid_X = floor(static_cast<float>(die_->getWidth() / averageWidth) * 0.2);
  int number_of_grid_Y = floor(static_cast<float>(die_->getHeight() / averageHeight) * 0.2);
  if (number_of_grid_X > 40)
    number_of_grid_X = 40;
  if (number_of_grid_Y > 40)
    number_of_grid_Y = 40;

  return pair<int, int>{number_of_grid_X, number_of_grid_Y};
}
bool Evaluator::densityCheck() {
  // get the average cell width and height
  pair<int, int> number_of_grid;
  number_of_grid = getBinNumbers();
  uint die_width = die_->getWidth();
  uint die_height = die_->getHeight();
  uint64 bin_width = static_cast<int>(die_width / number_of_grid.first);
  uint64 bin_height = static_cast<int>(die_height / number_of_grid.second);

  // grid setting
  class Bin {
   public:
    Bin() = default;
    explicit Bin(pair<int, int> lower_left, pair<int, int> upper_right)
        : lower_left_(std::move(lower_left)), upper_right_(std::move(upper_right)) {}
    pair<int, int> lower_left_;
    pair<int, int> upper_right_;
    uint64 cell_area_{0};
    void getOverlapArea(Instance *instance) {
      pair<int, int> instance_lower_left = instance->getCoordinate();
      pair<int, int> instance_upper_right {
          instance_lower_left.first + (int) instance->getWidth(),
          instance_lower_left.second + (int) instance->getHeight()
      };
      int rectLx = max(this->lower_left_.first, instance_lower_left.first);
      int rectLy = max(this->lower_left_.second, instance_lower_left.second);
      int rectUx = min(this->upper_right_.first, instance_upper_right.first);
      int rectUy = min(this->upper_right_.second, instance_upper_right.second);

      int overlapWidth = rectUx - rectLx;
      int overlapHeight = rectUy - rectLy;

      if (overlapWidth < 0 || overlapHeight < 0) {
        return;
      }
      cell_area_ += (rectUx - rectLx) * (rectUy - rectLy);
    }
  };
  vector<vector<Bin>> bins2D;
  for (int i = 0; i <= number_of_grid.first; ++i) {
    vector<Bin> bins1D;
    for (int j = 0; j <= number_of_grid.second; ++j) {
      pair<int, int> lower_left{i * bin_width, j * bin_height};
      pair<int, int> upper_right{(i + 1) * bin_width, (j + 1) * bin_height};
      bins1D.emplace_back(lower_left, upper_right);
    }
    bins2D.push_back(bins1D);
  }
  // get utility in each bins
  for (Instance *instance : instance_pointers_) {
    pair<int, int> instance_lower_left = instance->getCoordinate();
    pair<int, int> instance_upper_right{
        instance_lower_left.first + instance->getWidth(),
        instance_lower_left.second + instance->getHeight()
    };

    int left_idx = static_cast<int>(instance_lower_left.first / bin_width);
    int right_idx = static_cast<int>(instance_upper_right.first / bin_width);
    int lower_idx = static_cast<int>(instance_lower_left.second / bin_height);
    int upper_idx = static_cast<int>(instance_upper_right.second / bin_height);
    for (int j = left_idx; j <= right_idx; ++j) {
      for (int k = lower_idx; k <= upper_idx; ++k) {
        bins2D.at(j).at(k).getOverlapArea(instance);
      }
    }
  }


  // find bin which has max density
  // time complexity: O(mxm), m is bin numbers
  uint64 max_cell_area_in_bin = 0;
  Bin max_density_bin;
  for (int i = 0; i < number_of_grid.second; ++i) {
    for (int j = 0; j < number_of_grid.first; ++j) {
      if (max_cell_area_in_bin < bins2D.at(j).at(i).cell_area_) {
        max_density_bin = bins2D.at(j).at(i);
        max_cell_area_in_bin = max_density_bin.cell_area_;
      }
    }
  }

  auto max_density =
      static_cast<float>(max_cell_area_in_bin * 1e-10) / static_cast<float>(1e-10 * bin_height * bin_width);
  if (max_density > 1.2) {
    cout << "The overflow grid is " << endl
         << "(" << max_density_bin.lower_left_.first << ", " << max_density_bin.lower_left_.second << ")"
         << ", (" << max_density_bin.upper_right_.first << ", " << max_density_bin.upper_right_.second << ")"
         << "  (lower left), (upper right)" << endl
         << "(" << max_density_bin.lower_left_.first / this->getUnitOfMicro() << ", "
         << max_density_bin.lower_left_.second / this->getUnitOfMicro() << ")"
         << ", (" << max_density_bin.upper_right_.first / this->getUnitOfMicro() << ", "
         << max_density_bin.upper_right_.second / this->getUnitOfMicro() << ")"
         << "  (lower left), (upper right) in micro unit" << endl;
    cout << "Max density: " << max_density << endl;
    return false;
  } else {
    return true;
  }
}

}