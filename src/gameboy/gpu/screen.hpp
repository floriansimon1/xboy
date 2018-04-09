#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>
#include <cstdint>

#include "../types.hpp"

constexpr unsigned int screenWidth   = 160;
constexpr unsigned int screenHeight  = 144;
constexpr unsigned int bitsPerPixel  = 2;
constexpr unsigned int bytesPerColor = 4;

const sf::Color black     = { 0,   0,   0   };
const sf::Color darkGrey  = { 96,  96,  96  };
const sf::Color lightGrey = { 192, 192, 192 };
const sf::Color white     = { 255, 255, 255 };

constexpr size_t frameSize = screenWidth * screenHeight * bytesPerColor;

// List of frame lines, pixel-by-pixel. A pixels is 32 bits (r, g, b, a).
using FrameBuffer = uint8_t[frameSize];

struct Screen {
  virtual void display(const FrameBuffer &frameBuffer) = 0;
};

void writeColor(FrameBuffer &frameBuffer, Coordinate x, Coordinate y, const sf::Color &color);
bool pixelIsWhite(const FrameBuffer &frameBuffer, Coordinate x, Coordinate y);

#endif
