#include "../../gameboy.hpp"
#include "../../../bit.hpp"
#include "negate.hpp"

Negate::Negate(): ConstantTimeInstruction(4, 0, 1) {
}

void Negate::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, ~(
    gameboy.cpu.singleByteRegister(&Cpu::af, false)
  ));

  gameboy.cpu.setSubtractFlag(true);
  gameboy.cpu.setHalfCarryFlag(true);
}

std::string Negate::toString() const {
  return "CPL";
}
