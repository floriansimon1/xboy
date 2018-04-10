#include <iostream>

#include "../../src/gameboy/gpu/graphical-objects.hpp"
#include "tile-test.hpp"

TileTest::TileTest(): Test("Tile test") {
}

bool TileTest::run() {
  TileConfiguration configuration;
  Mmu               mmu;

  /*
  * No need to write tilemap data, because tilemaps only point to tile 0
  * because the MMU is initialized with 0s.
  *
  * Example taken from http://www.codeslinger.co.uk/pages/projects/gameboy/graphics.html.
  */
  mmu.write(tileset1 + 1, 0b10101110);
  mmu.write(tileset1,     0b00110101);

  configuration.useTileset0            = false;
  configuration.tilesetStart           = tileset1;
  configuration.backgroundTilemapStart = tilemap1;

  const Tile tile(mmu, configuration, true, 0, 0);

  if (
    readObjectPixel(mmu, tile, 0, 0) != 0b10
    || readObjectPixel(mmu, tile, 1, 0) != 0b00
    || readObjectPixel(mmu, tile, 2, 0) != 0b11
    || readObjectPixel(mmu, tile, 3, 0) != 0b01
    || readObjectPixel(mmu, tile, 4, 0) != 0b10
    || readObjectPixel(mmu, tile, 5, 0) != 0b11
    || readObjectPixel(mmu, tile, 6, 0) != 0b10
    || readObjectPixel(mmu, tile, 7, 0) != 0b01
  ) {
    std::cout << "(0, 0) => " << (unsigned int) readObjectPixel(mmu, tile, 0, 0) << " - " << 0b10 << "\n"
              << "(1, 0) => " << (unsigned int) readObjectPixel(mmu, tile, 1, 0) << " - " << 0b00 << "\n"
              << "(2, 0) => " << (unsigned int) readObjectPixel(mmu, tile, 2, 0) << " - " << 0b11 << "\n"
              << "(3, 0) => " << (unsigned int) readObjectPixel(mmu, tile, 3, 0) << " - " << 0b01 << "\n"
              << "(4, 0) => " << (unsigned int) readObjectPixel(mmu, tile, 4, 0) << " - " << 0b10 << "\n"
              << "(5, 0) => " << (unsigned int) readObjectPixel(mmu, tile, 5, 0) << " - " << 0b11 << "\n"
              << "(6, 0) => " << (unsigned int) readObjectPixel(mmu, tile, 6, 0) << " - " << 0b10 << "\n"
              << "(7, 0) => " << (unsigned int) readObjectPixel(mmu, tile, 7, 0) << " - " << 0b01
              << std::endl;

    return false;
  }

  return true;
}
