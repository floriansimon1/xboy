#include "../../bit.hpp"
#include "tile-data.hpp"
#include "../memory/display-control-register.hpp"

TileData::TileData(const Mmu &mmu) {
  const auto displayControlRegister = mmu.readDisplayControlRegister();

  const auto backgroundUsesTilemap0 = DisplayControlRegister::useBackgroundTileMap0(displayControlRegister);
  const auto windowUsesTilemap0     = DisplayControlRegister::useWindowTileMap0(displayControlRegister);

  useTileset0 = DisplayControlRegister::useTileSet0(displayControlRegister);

  tilesetStart           = useTileset0 ? tileset0 : tileset1;
  windowTilemapStart     = windowUsesTilemap0 ? tilemap0 : tilemap1;
  backgroundTilemapStart = backgroundUsesTilemap0 ? tilemap0 : tilemap1;
}

Tile TileData::read(const Mmu &mmu, bool background, Coordinate x, Coordinate y) const {
  const uint16_t tileNumberPosition = (y * tilemapHeight + x) * tileSize;
  const uint16_t tilemapAddress     = background ? backgroundTilemapStart : windowTilemapStart;

  Tile tile;

  const uint8_t unsignedTileIdentifier = mmu[tilemapAddress + tileNumberPosition];

  const int8_t tileIdentifier = useTileset0 ? unsignedTileIdentifier - 128 : unsignedTileIdentifier;

  // This works because for tileset 0, we store the center of the tileset instead of its beginning.
  const uint16_t tilePosition = (useTileset0 ? tileset0 : tileset1) + tileIdentifier;

  for (uint16_t i = 0; i < tileSize; i++) {
    tile[i] = mmu[tilePosition + i];
  }

  return tile;
}

Pixel readPixel(const Tile &tile, Coordinate x, Coordinate y) {
  const uint8_t position = x + y * tileWidth;

  const uint8_t lowByte  = tile[position / 8];
  const uint8_t highByte = tile[position / 8 + 1];

  const uint8_t bit = 7 - (position % 8);

  return (
    (static_cast<bool>(getBit(highByte, bit)) << 1)
    | static_cast<bool>(getBit(lowByte, bit))
  );
}
