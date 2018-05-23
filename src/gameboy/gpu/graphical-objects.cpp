#include "../../bit.hpp"
#include "../gameboy.hpp"
#include "graphical-objects.hpp"
#include "../memory/display-control-register.hpp"

constexpr uint8_t  xByte                    = 0;
constexpr uint8_t  yByte                    = 1;
constexpr uint8_t  xFlipBit                 = 5;
constexpr uint8_t  yFlipBit                 = 6;
constexpr uint8_t  spriteSize               = 4;
constexpr uint8_t  attributesByte           = 3;
constexpr uint8_t  spriteNumberByte         = 2;
constexpr uint8_t  paletteAddressBit        = 4;
constexpr uint8_t  backgroundPriorityBit    = 7;
constexpr uint16_t firstPalette             = 0xff48;
constexpr uint16_t secondPalette            = 0xff49;
constexpr uint16_t spritePixelsAddress      = 0x8000;
constexpr uint16_t spriteAttributesAddress  = 0xfe00;
constexpr uint16_t backgroundPaletteAddress = 0xff47;

TileConfiguration::TileConfiguration(const Gameboy &gameboy) {
  const auto displayControlRegister = gameboy.mmu.readDisplayControlRegister(gameboy);

  const auto backgroundUsesTilemap0 = DisplayControlRegister::useBackgroundTileMap0(displayControlRegister);
  const auto windowUsesTilemap0     = DisplayControlRegister::useWindowTileMap0(displayControlRegister);

  useUnsignedTileset = DisplayControlRegister::useUnsignedTileset(displayControlRegister);

  windowTilemapStart     = windowUsesTilemap0 ? tilemap0 : tilemap1;
  backgroundTilemapStart = backgroundUsesTilemap0 ? tilemap0 : tilemap1;
  tilesetStart           = useUnsignedTileset ? unsignedTileset : signedTileset;
}

Tile::Tile(const Gameboy &gameboy, const TileConfiguration &tileConfiguration, bool background, Coordinate x, Coordinate y) {
  const uint16_t tileNumberPosition = y * tilemapWidth + x;
  const uint16_t tilemapAddress     = background ? tileConfiguration.backgroundTilemapStart : tileConfiguration.windowTilemapStart;

  const uint8_t unsignedTileIdentifier = gameboy.mmu.read(gameboy, tilemapAddress + tileNumberPosition);

  const int8_t tileIdentifier = tileConfiguration.useUnsignedTileset ? unsignedTileIdentifier : unsignedTileIdentifier - 128;

  // This works because for tileset 0, we store the center of the tileset instead of its beginning.
  const uint16_t tilePosition = (
    (tileConfiguration.useUnsignedTileset ? unsignedTileset : signedTileset)
    + (tileIdentifier * tileSize)
  );

  palette       = gameboy.mmu.read(gameboy, backgroundPaletteAddress);
  pixelsAddress = tilePosition;
}

SpriteConfiguration::SpriteConfiguration(uint8_t displayControlRegister):
  height(DisplayControlRegister::useBigSprites(displayControlRegister) ? bigSpriteHeight : normalSpriteHeight)
{
}

Sprite::Sprite(const Gameboy &gameboy, const SpriteConfiguration &spriteConfiguration, uint8_t spriteNumber) {
  const uint16_t spriteConfigurationStart = spriteAttributesAddress + spriteNumber * spriteSize;

  // For some reason, we read x - 8 and y - 16...
  // http://www.codeslinger.co.uk/pages/projects/gameboy/graphics.html
  x = gameboy.mmu.read(gameboy, spriteConfigurationStart + xByte) + 8;
  y = gameboy.mmu.read(gameboy, spriteConfigurationStart + yByte) + 16;

  pixelsAddress = spritePixelsAddress + gameboy.mmu.read(gameboy, spriteConfigurationStart + spriteNumberByte);

  const auto attributes = gameboy.mmu.read(gameboy, spriteConfigurationStart + attributesByte);

  palette              = gameboy.mmu.read(gameboy, getBit(attributes, paletteAddressBit) ? secondPalette : firstPalette);
  backgroundPrioritary = getBit(attributes, backgroundPriorityBit);
  xFlip                = getBit(attributes, xFlipBit);
  yFlip                = getBit(attributes, yFlipBit);
  height               = spriteConfiguration.height;
}

Coordinate Sprite::transformX(Coordinate x) const {
  return xFlip ? spriteWidth - x : x;
}

Coordinate Sprite::transformY(Coordinate y) const {
  return yFlip ? height - y : y;
}

// http://www.huderlem.com/demos/gameboy2bpp.html
Pixel readObjectPixel(const Gameboy &gameboy, const GraphicalObject &object, Coordinate baseX, Coordinate baseY) {
  const auto bit      = 7 - object.transformX(baseX);
  const auto bytePair = object.transformY(baseY);

  const uint16_t position = bytePair * 2;

  const auto lowByte  = gameboy.mmu.read(gameboy, object.pixelsAddress + position);
  const auto highByte = gameboy.mmu.read(gameboy, object.pixelsAddress + position + 1);

  return (
    (static_cast<bool>(getBit(highByte, bit)) << 1)
    | static_cast<bool>(getBit(lowByte, bit))
  );
}
