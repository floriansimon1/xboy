#include "../../src/gameboy/gpu/gpu.hpp"
#include "pixel-test.hpp"

PixelTest::PixelTest(): Test("Pixel test") {
}

bool PixelTest::run() {
  const Palette palette11 = 0b11000000;
  const Palette palette10 = 0b00110000;
  const Palette palette01 = 0b00001100;
  const Palette palette00 = 0b00000011;

  if (
    translatePixel(palette11, 0b00)
    || translatePixel(palette11, 0b01)
    || translatePixel(palette11, 0b10)
    || translatePixel(palette11, 0b11) != 0b11
  ) {
    return false;
  }

  if (
    translatePixel(palette10, 0b00)
    || translatePixel(palette10, 0b01)
    || translatePixel(palette10, 0b11)
    || translatePixel(palette10, 0b10) != 0b11
  ) {
    return false;
  }

  if (
    translatePixel(palette01, 0b00)
    || translatePixel(palette01, 0b10)
    || translatePixel(palette01, 0b11)
    || translatePixel(palette01, 0b01) != 0b11
  ) {
    return false;
  }

  if (
    translatePixel(palette00, 0b01)
    || translatePixel(palette00, 0b10)
    || translatePixel(palette00, 0b11)
    || translatePixel(palette00, 0b00) != 0b11
  ) {
    return false;
  }

  return true;
}
