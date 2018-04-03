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

constexpr auto tileSize = (tileWidth * tileHeight * bitsPerPixel) / 8;

typedef std::array<uint8_t, tileSize> Tile;

struct TileData {
  bool     useTileset0;
  uint16_t tilesetStart;
  uint16_t windowTilemapStart;
  uint16_t backgroundTilemapStart;

  TileData(const Mmu &mmu);

  Tile read(const Mmu &mmu, bool background, Coordinate x, Coordinate y) const;
};

Pixel readPixel(const Tile &tile, Coordinate x, Coordinate y);

#endif
