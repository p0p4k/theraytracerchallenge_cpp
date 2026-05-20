#include "canvas.h"
#include <algorithm>
#include <cmath>
#include <string>

void Canvas::write_pixel(const int x, const int y, const Color &c) {
  canvas_color[y * width + x] = c;
}

Color Canvas::pixel_at(const int x, const int y) {
  return canvas_color[y * width + x];
}

std::string Canvas::canvas_to_ppm() {
  std::string ppm = "P3\n";
  ppm += std::to_string(width) + " " + std::to_string(height) + "\n";
  ppm += "255\n";

  std::string current_line = "";
  auto append_value = [&](int val) {
    std::string val_str = std::to_string(val);
    if (!current_line.empty()) {
      if (current_line.length() + 1 + val_str.length() > 70) {
        ppm += current_line + "\n";
        current_line = val_str;
      } else {
        current_line += " " + val_str;
      }
    } else {
      current_line = val_str;
    }
  };

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int r = std::clamp(
          static_cast<int>(std::round(canvas_color[i * width + j].r * 255.0)),
          0, 255);
      int g = std::clamp(
          static_cast<int>(std::round(canvas_color[i * width + j].g * 255.0)),
          0, 255);
      int b = std::clamp(
          static_cast<int>(std::round(canvas_color[i * width + j].b * 255.0)),
          0, 255);
      append_value(r);
      append_value(g);
      append_value(b);
    }
  }

  if (!current_line.empty()) {
    ppm += current_line + "\n";
  }

  return ppm;
}
