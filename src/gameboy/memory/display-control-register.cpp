#include "display-control-register.hpp"

const unsigned short enabledBit        = 7;
const unsigned short showWindowBit     = 5;
const unsigned short showSpritesBit    = 1;
const unsigned short showBackgroundBit = 0;

bool DisplayControlRegister::enabled(uint8_t value) {
  return getBit(value, enabledBit);
}

bool DisplayControlRegister::showBackground(uint8_t value) {
  return getBit(value, showBackgroundBit);
}

bool DisplayControlRegister::showSprites(uint8_t value) {
  return getBit(value, showSpritesBit);
}

bool DisplayControlRegister::showWindow(uint8_t value) {
  return getBit(value, showWindowBit);
}
