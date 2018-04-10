#include <iostream>

#include "../../src/gameboy/gpu/graphical-objects.hpp"
#include "../../src/gameboy/gameboy.hpp"
#include "tile-test.hpp"

TileTest::TileTest(): Test("Tile test") {
}

bool TileTest::run() {
  TileConfiguration configuration;
  Gameboy           gameboy;

  /*
  * No need to write tilemap data, because tilemaps only point to tile 0
  * because the MMU is initialized with 0s.
  *
  * Example taken from http://www.codeslinger.co.uk/pages/projects/gameboy/graphics.html.
  */
  gameboy.mmu.write(gameboy, tileset1 + 1, 0b10101110);
  gameboy.mmu.write(gameboy, tileset1,     0b00110101);

  configuration.useTileset0            = false;
  configuration.tilesetStart           = tileset1;
  configuration.backgroundTilemapStart = tilemap1;

  const Tile tile(gameboy, configuration, true, 0, 0);

  if (
    readObjectPixel(gameboy, tile, 0, 0) != 0b10
    || readObjectPixel(gameboy, tile, 1, 0) != 0b00
    || readObjectPixel(gameboy, tile, 2, 0) != 0b11
    || readObjectPixel(gameboy, tile, 3, 0) != 0b01
    || readObjectPixel(gameboy, tile, 4, 0) != 0b10
    || readObjectPixel(gameboy, tile, 5, 0) != 0b11
    || readObjectPixel(gameboy, tile, 6, 0) != 0b10
    || readObjectPixel(gameboy, tile, 7, 0) != 0b01
  ) {
    std::cout << "(0, 0) => " << (unsigned int) readObjectPixel(gameboy, tile, 0, 0) << " - " << 0b10 << "\n"
              << "(1, 0) => " << (unsigned int) readObjectPixel(gameboy, tile, 1, 0) << " - " << 0b00 << "\n"
              << "(2, 0) => " << (unsigned int) readObjectPixel(gameboy, tile, 2, 0) << " - " << 0b11 << "\n"
              << "(3, 0) => " << (unsigned int) readObjectPixel(gameboy, tile, 3, 0) << " - " << 0b01 << "\n"
              << "(4, 0) => " << (unsigned int) readObjectPixel(gameboy, tile, 4, 0) << " - " << 0b10 << "\n"
              << "(5, 0) => " << (unsigned int) readObjectPixel(gameboy, tile, 5, 0) << " - " << 0b11 << "\n"
              << "(6, 0) => " << (unsigned int) readObjectPixel(gameboy, tile, 6, 0) << " - " << 0b10 << "\n"
              << "(7, 0) => " << (unsigned int) readObjectPixel(gameboy, tile, 7, 0) << " - " << 0b01
              << std::endl;

    return false;
  }

  return true;
}
