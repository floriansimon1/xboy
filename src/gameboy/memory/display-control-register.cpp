#include "display-control-register.hpp"

const unsigned short enabledBit = 7;

bool DisplayControlRegister::enabled(uint8_t value) {
  return getBit(enabledBit, value);
}
