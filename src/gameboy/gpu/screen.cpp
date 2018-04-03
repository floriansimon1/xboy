#include "screen.hpp"

void writeColor(FrameBuffer &frameBuffer, Coordinate x, Coordinate y, const sf::Color &color) {
  const auto position = (x + y * screenWidth) * bytesPerColor;

  frameBuffer[position]     = color.r;
  frameBuffer[position + 1] = color.g;
  frameBuffer[position + 2] = color.b;
}
