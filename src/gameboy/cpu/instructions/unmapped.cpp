#include <iostream>

#include "unmapped.hpp"
#include "../../gameboy.hpp"

Unmapped::Unmapped(): ConstantTimeInstruction(0, 0, 1) {
}

void Unmapped::execute(Gameboy &, const uint8_t *) const {
  std::cout << "Error: UNMAPPED instruction found!" << std::endl;
}

std::string Unmapped::toString() const {
  return "UNMAPPED";
}
