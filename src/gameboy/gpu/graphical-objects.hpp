#ifndef TILE_DATA_HPP
#define TILE_DATA_HPP

#include <array>

#include "screen.hpp"
#include "../types.hpp"
#include "../memory/mmu.hpp"

constexpr uint8_t tileWidth     = 8;
constexpr uint8_t tileHeight    = 8;
constexpr uint8_t tilemapWidth  = 32;
constexpr uint8_t tilemapHeight = 32;

// See http://imrannazar.com/GameBoy-Emulation-in-JavaScript:-Graphics
constexpr uint16_t tileset1 = 0x8800;
constexpr uint16_t tileset0 = 0x9000;
constexpr uint16_t tilemap1 = 0x9800;
constexpr uint16_t tilemap0 = 0x9c00;

constexpr auto tileSize = (tileWidth * tileHeight * bitsPerPixel) / 8;

constexpr unsigned short numberOfSprites = 40;

struct GraphicalObject {
  uint16_t pixelsAddress;
};

struct SpriteData {
  bool bigSprites;

  SpriteData(uint8_t displayControlRegister);
};

struct TileData {
  bool     useTileset0;
  uint16_t tilesetStart;
  uint16_t windowTilemapStart;
  uint16_t backgroundTilemapStart;

  TileData() = default;
  TileData(const Mmu &mmu);
};

struct Sprite: GraphicalObject {
  bool     backgroundPrioritary;
  uint16_t paletteAddress;
  bool     yFlip;
  bool     xFlip;
  uint8_t  x;
  uint8_t  y;

  Sprite(const Mmu &mmu, uint8_t spriteNumber);
};

struct Tile: GraphicalObject {
  Tile(const Mmu &mmu, const TileData &tileData, bool background, Coordinate x, Coordinate y);
};

Pixel readObjectPixel(const Mmu &mmu, const GraphicalObject &object, Coordinate x, Coordinate y);

#endif
