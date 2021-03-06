#include "display-control-register.hpp"

const unsigned short enabledBit               = 7;
const unsigned short bigSpritesBit            = 2;
const unsigned short showWindowBit            = 5;
const unsigned short showSpritesBit           = 1;
const unsigned short tilesetSelectBit         = 4;
const unsigned short showBackgroundBit        = 0;
const unsigned short useWindowTileMap0Bit     = 3;
const unsigned short useBackgroundTileMap0Bit = 6;

bool DisplayControlRegister::useBigSprites(uint8_t value) {
  return getBit(value, bigSpritesBit);
}

bool DisplayControlRegister::useUnsignedTileset(uint8_t value) {
  return getBit(value, tilesetSelectBit);
}

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

bool DisplayControlRegister::useBackgroundTileMap0(uint8_t value) {
  return !getBit(value, useBackgroundTileMap0Bit);
}

bool DisplayControlRegister::useWindowTileMap0(uint8_t value) {
  return !getBit(value, useWindowTileMap0Bit);
}
