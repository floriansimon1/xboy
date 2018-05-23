#ifndef TILE_DATA_HPP
#define TILE_DATA_HPP

#include <array>

#include "screen.hpp"
#include "../types.hpp"

struct Gameboy;

constexpr uint8_t tileWidth     = 8;
constexpr uint8_t tileHeight    = 8;
constexpr uint8_t tilemapWidth  = 32;
constexpr uint8_t tilemapHeight = 32;

// See http://imrannazar.com/GameBoy-Emulation-in-JavaScript:-Graphics
constexpr uint16_t tilemap1        = 0x9c00;
constexpr uint16_t tilemap0        = 0x9800;
constexpr uint16_t signedTileset   = 0x9000;
constexpr uint16_t unsignedTileset = 0x8000;

// In bytes
constexpr auto tileSize = (tileWidth * tileHeight * bitsPerPixel) / 8;

constexpr uint8_t numberOfSprites    = 40;
constexpr uint8_t bigSpriteHeight    = 16;
constexpr uint8_t normalSpriteHeight = 8;
constexpr uint8_t spriteWidth        = 8;

struct GraphicalObject {
  uint16_t pixelsAddress;
  Palette  palette;

  virtual Coordinate transformX(Coordinate x) const { return x; }
  virtual Coordinate transformY(Coordinate y) const { return y; }
};

struct SpriteConfiguration {
  uint8_t height;

  SpriteConfiguration(uint8_t displayControlRegister);
};

struct TileConfiguration {
  uint16_t tilesetStart;
  uint16_t windowTilemapStart;
  bool     useUnsignedTileset;
  uint16_t backgroundTilemapStart;

  TileConfiguration() = default;
  TileConfiguration(const Gameboy &gameboy);
};

struct Sprite: GraphicalObject {
  bool    backgroundPrioritary;
  uint8_t height;
  bool    yFlip;
  bool    xFlip;
  uint8_t x;
  uint8_t y;

  Sprite(const Gameboy &gameboy, const SpriteConfiguration &SpriteConfiguration, uint8_t spriteNumber);

  virtual Coordinate transformX(Coordinate x) const override;
  virtual Coordinate transformY(Coordinate y) const override;
};

struct Tile: GraphicalObject {
  Tile(const Gameboy &gameboy, const TileConfiguration &tileConfiguration, bool background, Coordinate x, Coordinate y);
};

Pixel readObjectPixel(const Gameboy &gameboy, const GraphicalObject &object, Coordinate x, Coordinate y);

#endif
