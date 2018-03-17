#include "immediate-and.hpp"
#include "../../gameboy.hpp"
#include "../../../bit.hpp"

ImmediateAnd::ImmediateAnd(): ConstantTimeInstruction(8, 1, 1) {
}

void ImmediateAnd::execute(Gameboy &gameboy, const uint8_t *data) const {
  gameboy.cpu.setHalfCarryFlag(true);
  gameboy.cpu.setSubtractFlag(false);
  gameboy.cpu.setCarryFlag(false);

  const auto a = gameboy.cpu.singleByteRegister(&Cpu::af, false);

  const auto result = a & *data;

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, result);

  gameboy.cpu.setZeroFlag(!result);
}

std::string ImmediateAnd::toString() const {
  return "AND d8";
}
