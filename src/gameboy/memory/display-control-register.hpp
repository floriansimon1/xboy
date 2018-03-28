#ifndef DISPLAY_CONTROL_REGISTER_HPP
#define DISPLAY_CONTROL_REGISTER_HPP

#include "../../bit.hpp"

namespace DisplayControlRegister {
  constexpr uint16_t address = 0xff40;

  bool enabled(uint8_t value);
};

#endif
