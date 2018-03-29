#ifndef TILE_DATA_HPP
#define TILE_DATA_HPP

#include "../memory/mmu.hpp"

struct TileData {
  bool     useTileset0;
  uint16_t tilesetStart;
  uint16_t windowTilemapStart;
  uint16_t backgroundTilemapStart;

  TileData(const Mmu &mmu);
};

#endif
