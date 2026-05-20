#ifndef CANVAS_H
#define CANVAS_H

#include "color.h"
#include <string>
#include <vector>

class Canvas {
public:
  int width, height;
  std::vector<Color> canvas_color;
  Canvas(int width, int height)
      : width(width), height(height),
        canvas_color(width * height, Color(0, 0, 0)) {}

  void write_pixel(const int x, const int y, const Color &c);
  Color pixel_at(const int x, const int y);

  std::string canvas_to_ppm();
};

#endif
