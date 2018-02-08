#include "halt.hpp"
#include "../../gameboy.hpp"

Halt::Halt(): ConstantTimeInstruction(4, 0, 1) {
}

void Halt::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.halted = true;
}

std::string Halt::toString() const {
  return "HALT";
}
