#ifndef SPRITE_DATA_HPP
#define SPRITE_DATA_HPP

#include "../memory/mmu.hpp"

constexpr unsigned short numberOfSprites = 40;

struct SpriteData {
  bool bigSprites;

  SpriteData(uint8_t displayControlRegister);
};

struct Sprite {
  bool     backgroundPrioritary;
  uint16_t paletteAddress;
  uint16_t address;
  bool     yFlip;
  bool     xFlip;
  uint8_t  x;
  uint8_t  y;

  Sprite(const Mmu &mmu, uint8_t spriteNumber);
};

#endif
