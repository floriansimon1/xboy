#include <iostream>

#include "../../src/gameboy/gpu/tile-data.hpp"
#include "tile-test.hpp"

TileTest::TileTest(): Test("Tile test") {
}

bool TileTest::run() {
  TileData data;
  Mmu      mmu;

  /*
  * No need to write tilemap data, because tilemaps only point to tile 0
  * because the MMU is initialized with 0s.
  *
  * Example taken from http://www.codeslinger.co.uk/pages/projects/gameboy/graphics.html.
  */
  mmu.write(tileset1 + 1, 0b10101110);
  mmu.write(tileset1,     0b00110101);

  data.useTileset0            = false;
  data.tilesetStart           = tileset1;
  data.backgroundTilemapStart = tilemap1;

  const Tile tile = data.read(mmu, true, 0, 0);

  if (
    readPixel(tile, 0, 0) != 0b10
    || readPixel(tile, 1, 0) != 0b00
    || readPixel(tile, 2, 0) != 0b11
    || readPixel(tile, 3, 0) != 0b01
    || readPixel(tile, 4, 0) != 0b10
    || readPixel(tile, 5, 0) != 0b11
    || readPixel(tile, 6, 0) != 0b10
    || readPixel(tile, 7, 0) != 0b01
  ) {
    std::cout << "(0, 0) => " << (unsigned int) readPixel(tile, 0, 0) << " - " << 0b10 << "\n"
              << "(1, 0) => " << (unsigned int) readPixel(tile, 1, 0) << " - " << 0b00 << "\n"
              << "(2, 0) => " << (unsigned int) readPixel(tile, 2, 0) << " - " << 0b11 << "\n"
              << "(3, 0) => " << (unsigned int) readPixel(tile, 3, 0) << " - " << 0b01 << "\n"
              << "(4, 0) => " << (unsigned int) readPixel(tile, 4, 0) << " - " << 0b10 << "\n"
              << "(5, 0) => " << (unsigned int) readPixel(tile, 5, 0) << " - " << 0b11 << "\n"
              << "(6, 0) => " << (unsigned int) readPixel(tile, 6, 0) << " - " << 0b10 << "\n"
              << "(7, 0) => " << (unsigned int) readPixel(tile, 7, 0) << " - " << 0b01
              << std::endl;

    return false;
  }

  return true;
}
