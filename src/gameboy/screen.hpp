#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <cstdint>

constexpr unsigned int screenWidth  = 160;
constexpr unsigned int screenHeight = 144;

// List of frame lines, pixel-by-pixel. A pixels is 32 bits (r, g, b, a).
using Frame = uint8_t[screenWidth * screenHeight * 4];

struct Screen {
  virtual void display(Frame &frame) = 0;
};

#endif
