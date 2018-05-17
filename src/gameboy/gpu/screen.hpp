#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>
#include <cstdint>

#include "../types.hpp"

constexpr unsigned int screenWidth   = 160;
constexpr unsigned int screenHeight  = 144;
constexpr unsigned int bitsPerPixel  = 2;
constexpr unsigned int bytesPerColor = 4;

struct Color { unsigned short r; unsigned short g; unsigned short b; };

const Color black     = { 0,   0,   0   };
const Color darkGrey  = { 96,  96,  96  };
const Color lightGrey = { 192, 192, 192 };
const Color white     = { 255, 255, 255 };

constexpr size_t frameSize = screenWidth * screenHeight * bytesPerColor;

struct FrameBuffer {
  virtual void setPixel(Coordinate x, Coordinate y, const Color &color) = 0;
  virtual Color getPixel(Coordinate x, Coordinate y) const = 0;
  virtual ~FrameBuffer() = default;

  bool pixelIsWhite(Coordinate x, Coordinate y) const;
};

struct Screen {
  virtual void display() = 0;
  virtual ~Screen() = default;
  virtual FrameBuffer& getFrameBuffer() = 0;
};

#endif
