#include "screen.hpp"

bool FrameBuffer::pixelIsWhite(Coordinate x, Coordinate y) const {
  const auto color = getPixel(x, y);

  return (
    color.red == white.red
    && color.blue == white.blue
    && color.green == white.green
  );
}
