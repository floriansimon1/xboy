#include "invert-carry-flag.hpp"
#include "../../gameboy.hpp"

InvertCarryFlag::InvertCarryFlag(): Instruction(4, 0, 1) {
}

void InvertCarryFlag::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setSubtractFlag(false);
  gameboy.cpu.setHalfCarryFlag(false);
  gameboy.cpu.setCarryFlag(gameboy.cpu.getCarryFlag());
}

std::string InvertCarryFlag::toString() const {
  return "CCF";
}
