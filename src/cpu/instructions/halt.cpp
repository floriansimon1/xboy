#include "halt.hpp"
#include "../../gameboy.hpp"

Halt::Halt(): ConstantTimeInstruction(4, 0, 1) {
}

void Halt::execute(Gameboy &, const uint8_t *) const {
  throw "Not implemented yet!";
}

std::string Halt::toString() const {
  return "HALT";
}
