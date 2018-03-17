#include "immediate-compare.hpp"
#include "../../gameboy.hpp"
#include "../../../bit.hpp"

ImmediateCompare::ImmediateCompare(): ConstantTimeInstruction(8, 1, 1), subtractionInstruction(false) {
}

void ImmediateCompare::execute(Gameboy &gameboy, const uint8_t *data) const {
  const auto a = gameboy.cpu.singleByteRegister(&Cpu::af, false);

  subtractionInstruction.execute(gameboy, data);

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, a);
}

std::string ImmediateCompare::toString() const {
  return "CP d8";
}
