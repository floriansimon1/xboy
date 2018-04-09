#include "sprite-data.hpp"
#include "../memory/display-control-register.hpp"

constexpr uint8_t  xByte                 = 0;
constexpr uint8_t  yByte                 = 1;
constexpr uint8_t  xFlipBit              = 5;
constexpr uint8_t  yFlipBit              = 6;
constexpr uint8_t  spriteSize            = 4;
constexpr uint8_t  attributesByte        = 3;
constexpr uint8_t  spriteNumberByte      = 2;
constexpr uint8_t  paletteAddressBit     = 4;
constexpr uint8_t  backgroundPriorityBit = 7;
constexpr uint16_t firstPalette          = 0xff48;
constexpr uint16_t secondPalette         = 0xff49;
constexpr uint16_t spriteMapAddress      = 0x8000;
constexpr uint16_t spriteSetAddress      = 0xfe00;

SpriteData::SpriteData(uint8_t displayControlRegister):
  bigSprites(DisplayControlRegister::useBigSprites(displayControlRegister))
{
}

Sprite::Sprite(const Mmu &mmu, uint8_t spriteNumber) {
  const uint16_t spriteDataStart = spriteSetAddress + spriteNumber * spriteSize;

  x       = mmu[spriteDataStart + xByte];
  y       = mmu[spriteDataStart + yByte];
  address = spriteMapAddress + mmu[spriteDataStart + spriteNumberByte];

  const auto attributes = mmu[spriteDataStart + attributesByte];

  paletteAddress       = getBit(attributes, paletteAddressBit) ? secondPalette : firstPalette;
  backgroundPrioritary = getBit(attributes, backgroundPriorityBit);
  xFlip                = getBit(attributes, xFlipBit);
  yFlip                = getBit(attributes, yFlipBit);
}
