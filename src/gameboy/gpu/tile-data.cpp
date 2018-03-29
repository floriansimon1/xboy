#include "tile-data.hpp"
#include "../memory/display-control-register.hpp"

// See http://imrannazar.com/GameBoy-Emulation-in-JavaScript:-Graphics
constexpr uint16_t tileset1 = 0x8800;
constexpr uint16_t tileset0 = 0x9000;
constexpr uint16_t tilemap1 = 0x9800;
constexpr uint16_t tilemap0 = 0x9c00;

TileData::TileData(const Mmu &mmu) {
  const auto displayControlRegister = mmu.readDisplayControlRegister();

  const auto backgroundUsesTilemap0 = DisplayControlRegister::useBackgroundTileMap0(displayControlRegister);
  const auto windowUsesTilemap0     = DisplayControlRegister::useWindowTileMap0(displayControlRegister);

  useTileset0 = DisplayControlRegister::useTileSet0(displayControlRegister);

  tilesetStart           = useTileset0 ? tileset0 : tileset1;
  windowTilemapStart     = windowUsesTilemap0 ? tilemap0 : tilemap1;
  backgroundTilemapStart = backgroundUsesTilemap0 ? tilemap0 : tilemap1;
}
