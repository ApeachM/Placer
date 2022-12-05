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
#include <ctime>
#include "visualizer.h"
namespace Placer {
int scale_factor;
void drawDie(Image &image, Placer::Die *die) {
  int lower_left_x = MARGIN;
  int lower_left_y = MARGIN;
  int upper_right_x = static_cast<int>(die->getWidth()) / scale_factor + MARGIN;
  int upper_right_y = static_cast<int>(die->getHeight()) / scale_factor + MARGIN;
  image.draw_rectangle(lower_left_x, lower_left_y, upper_right_x, upper_right_y, Color::DIM_GRAY);
}
void drawCell(Image &image, Instance *cell) {
  pair<int, int> cell_coordinate = cell->getCoordinate();
  int lower_left_x = (cell_coordinate.first) / scale_factor + MARGIN;
  int lower_left_y = (cell_coordinate.second + MARGIN) / scale_factor + MARGIN;
  int upper_right_x = (cell_coordinate.first + static_cast<int>(cell->getWidth())) / scale_factor + MARGIN;
  int upper_right_y = (cell_coordinate.second + static_cast<int>(cell->getHeight())) / scale_factor + MARGIN;
  if (lower_left_x == upper_right_x)
    upper_right_x = lower_left_x + 1;
  if (lower_left_y == upper_right_y)
    upper_right_y = lower_left_y + 1;

  image.draw_rectangle(lower_left_x, lower_left_y, upper_right_x, upper_right_y, Color::BLACK);
}
void drawNet(Image &image, Placer::Net *net) {
  int center_x = 0, center_y = 0;
  for (auto pin : net->getConnectedPins()) {
    // if the connected cells are not placed
    if (!pin->getInstance())
      continue;
    if (!pin->getInstance()->isPlaced())
      assert(0);
    center_x += pin->getCoordinate().first;
    center_y += pin->getCoordinate().second;
  }

  center_x /= static_cast<int>(net->getConnectedPins().size());
  center_y /= static_cast<int>(net->getConnectedPins().size());

  int x1 = (center_x) / scale_factor + MARGIN;
  int y1 = (center_y) / scale_factor + MARGIN;

  for (auto pin : net->getConnectedPins()) {
    int x2 = (pin->getCoordinate().first) / scale_factor + MARGIN;
    int y2 = (pin->getCoordinate().second) / scale_factor + MARGIN;
    image.draw_line(x1, y1, x2, y2, Color::RED);
  }

}
void drawPad(Image &image, Placer::Pin *pin) {
  int pad_half_width = 2;
  int pad_half_height = 2;
  int x = pin->getCoordinate().first / scale_factor + MARGIN;
  int y = pin->getCoordinate().second / scale_factor + MARGIN;
  image.draw_rectangle(x - pad_half_width,
                       y - pad_half_height,
                       x + pad_half_width,
                       y + pad_half_height,
                       Color::BLUE);
}
void Circuit::saveImg(const string &file_name) {
  // define the image size 2000x2000 pixel
  int img_width = 2000;

  // define the scale factor
  // let the scale factor make the image size as approximately 2000x2000 pixel
  scale_factor = static_cast<int>(die_->getHeight()) / img_width;
  uint64 die_width = die_->getWidth();
  uint64 die_height = die_->getHeight();

  // define MARGIN
  MARGIN = static_cast<int>(die_->getHeight()) / 20;
  MARGIN /= scale_factor;

  Image image((die_width) / scale_factor + 2 * MARGIN, (die_height) / scale_factor + 2 * MARGIN, 1, 3, 255);
  drawDie(image, die_);

  for (Net *net : net_pointers_) {
    drawNet(image, net);
  }
  for (Instance *instance : instance_pointers_) {
    drawCell(image, instance);
  }
  for (Pin *io_pad : pad_pointers_) {
    drawPad(image, io_pad);
  }

  // image save
  string file_path = "../output/images/" + file_name + ".bmp";
  const char *file_path_char = file_path.c_str();
  image.save(file_path_char);
}
}