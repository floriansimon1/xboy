#ifndef DISPLAY_CONTROL_REGISTER_HPP
#define DISPLAY_CONTROL_REGISTER_HPP

#include "../../bit.hpp"

namespace DisplayControlRegister {
  constexpr uint16_t address = 0xff40;

  bool useBackgroundTileMap0(uint8_t value);
  bool useUnsignedTileset(uint8_t value);
  bool useWindowTileMap0(uint8_t value);
  bool showBackground(uint8_t value);
  bool useBigSprites(uint8_t value);
  bool showSprites(uint8_t value);
  bool showWindow(uint8_t value);
  bool enabled(uint8_t value);
};

#endif
