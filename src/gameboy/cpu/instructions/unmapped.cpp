#include "unmapped.hpp"
#include "../../gameboy.hpp"

Unmapped::Unmapped(): ConstantTimeInstruction(0, 0, 1) {
}

void Unmapped::execute(Gameboy &, const uint8_t *) const {
}

std::string Unmapped::toString() const {
  return "UNMAPPED";
}
