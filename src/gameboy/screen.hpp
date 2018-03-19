#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <cstdint>

constexpr unsigned int screenWidth  = 160;
constexpr unsigned int screenHeight = 144;

constexpr size_t frameSize = screenWidth * screenHeight * 4;

// List of frame lines, pixel-by-pixel. A pixels is 32 bits (r, g, b, a).
using Frame = uint8_t[frameSize];

struct Screen {
  virtual void display(const Frame &frame) = 0;
};

#endif
