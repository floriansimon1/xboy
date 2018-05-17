#include "screen.hpp"

bool FrameBuffer::pixelIsWhite(Coordinate x, Coordinate y) const {
  const auto color = getPixel(x, y);

  return (
    color.r == white.r
    && color.g == white.g
    && color.b == white.b
  );
}
