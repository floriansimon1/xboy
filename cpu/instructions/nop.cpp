#include "nop.hpp"
#include "../../gameboy.hpp"

Nop::Nop(): Instruction(4, 0, 1) {
}

void Nop::execute(Gameboy &, const uint8_t *) const {
}

std::string Nop::toString() const {
  return "NOP";
}
