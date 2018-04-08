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

typedef std::array<uint8_t, tileSize> Tile;

struct TileData {
  bool     useTileset0;
  uint16_t tilesetStart;
  uint16_t windowTilemapStart;
  uint16_t backgroundTilemapStart;

  TileData() = default;
  TileData(const Mmu &mmu);

  Tile read(const Mmu &mmu, bool background, Coordinate x, Coordinate y) const;
};

Pixel readPixel(const Tile &tile, Coordinate x, Coordinate y);

#endif
