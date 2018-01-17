#include "stop.hpp"
#include "../../gameboy.hpp"

// The data byte is always 0 and ignored.
Stop::Stop(): Instruction(4, 1, 1) {
}

void Stop::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.lowPowerMode = true;
}

std::string Stop::toString() const {
  return "STOP 0";
}
