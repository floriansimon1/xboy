#include <sstream>

#include "subtract-memory-byte-to-register.hpp"
#include "../../../debug/register-string.hpp"
#include "../../gameboy.hpp"

SubtractMemoryByteToRegister::SubtractMemoryByteToRegister(CpuRegisterPointer pointerRegister, bool carry):
  ConstantTimeInstruction(8, 0, 1),
  subtractionInstruction(carry),
  pointerRegister(pointerRegister)
{
}

void SubtractMemoryByteToRegister::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.mmu[gameboy.cpu.twoBytesRegister(pointerRegister)];

  subtractionInstruction.execute(gameboy, &value);
}

std::string SubtractMemoryByteToRegister::toString() const {
  std::ostringstream result;

  result << subtractionInstruction.mnemonic() << " (" << registerString(pointerRegister, false, false) << ")";

  return result.str();
}
