#include "../../bit.hpp"
#include "graphical-objects.hpp"
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

TileData::TileData(const Mmu &mmu) {
  const auto displayControlRegister = mmu.readDisplayControlRegister();

  const auto backgroundUsesTilemap0 = DisplayControlRegister::useBackgroundTileMap0(displayControlRegister);
  const auto windowUsesTilemap0     = DisplayControlRegister::useWindowTileMap0(displayControlRegister);

  useTileset0 = DisplayControlRegister::useTileSet0(displayControlRegister);

  tilesetStart           = useTileset0 ? tileset0 : tileset1;
  windowTilemapStart     = windowUsesTilemap0 ? tilemap0 : tilemap1;
  backgroundTilemapStart = backgroundUsesTilemap0 ? tilemap0 : tilemap1;
}

Tile::Tile(const Mmu &mmu, const TileData &tileData, bool background, Coordinate x, Coordinate y) {
  const uint16_t tileNumberPosition = (y * tilemapHeight + x) * tileSize;
  const uint16_t tilemapAddress     = background ? tileData.backgroundTilemapStart : tileData.windowTilemapStart;

  const uint8_t unsignedTileIdentifier = mmu[tilemapAddress + tileNumberPosition];

  const int8_t tileIdentifier = tileData.useTileset0 ? unsignedTileIdentifier - 128 : unsignedTileIdentifier;

  // This works because for tileset 0, we store the center of the tileset instead of its beginning.
  const uint16_t tilePosition = (tileData.useTileset0 ? tileset0 : tileset1) + tileIdentifier;

  pixelsAddress = tilePosition;
}

SpriteData::SpriteData(uint8_t displayControlRegister):
  bigSprites(DisplayControlRegister::useBigSprites(displayControlRegister))
{
}

Sprite::Sprite(const Mmu &mmu, uint8_t spriteNumber) {
  const uint16_t spriteDataStart = spriteSetAddress + spriteNumber * spriteSize;

  x             = mmu[spriteDataStart + xByte];
  y             = mmu[spriteDataStart + yByte];
  pixelsAddress = spriteMapAddress + mmu[spriteDataStart + spriteNumberByte];

  const auto attributes = mmu[spriteDataStart + attributesByte];

  paletteAddress       = getBit(attributes, paletteAddressBit) ? secondPalette : firstPalette;
  backgroundPrioritary = getBit(attributes, backgroundPriorityBit);
  xFlip                = getBit(attributes, xFlipBit);
  yFlip                = getBit(attributes, yFlipBit);
}

Pixel readObjectPixel(const Mmu &mmu, const GraphicalObject &object, Coordinate x, Coordinate y) {
  const uint8_t position = x + y * tileWidth;

  const uint8_t lowByte  = mmu[object.pixelsAddress + position / 8];
  const uint8_t highByte = mmu[object.pixelsAddress + position / 8 + 1];

  const uint8_t bit = 7 - (position % 8);

  return (
    (static_cast<bool>(getBit(highByte, bit)) << 1)
    | static_cast<bool>(getBit(lowByte, bit))
  );
}
