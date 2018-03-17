#include "set-carry-flag.hpp"
#include "../../gameboy.hpp"

SetCarryFlag::SetCarryFlag(): ConstantTimeInstruction(4, 0, 1) {
}

void SetCarryFlag::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setCarryFlag(true);
  gameboy.cpu.setSubtractFlag(false);
  gameboy.cpu.setHalfCarryFlag(false);
}

std::string SetCarryFlag::toString() const {
  return "SCF";
}
