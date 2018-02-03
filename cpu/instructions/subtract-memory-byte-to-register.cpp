#include <sstream>

#include "subtract-memory-byte-to-register.hpp"
#include "../../debug/register-string.hpp"
#include "../../gameboy.hpp"

SubtractMemoryByteToRegister::SubtractMemoryByteToRegister(CpuRegisterPointer pointerRegister, bool carry):
  Instruction(8, 0, 1),
  subtractionInstruction(carry),
  pointerRegister(pointerRegister),
  carry(carry)
{
}

void SubtractMemoryByteToRegister::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto valuePointer = gameboy.mmu.memory + gameboy.cpu.twoBytesRegister(pointerRegister);

  subtractionInstruction.execute(gameboy, valuePointer);
}

std::string SubtractMemoryByteToRegister::toString() const {
  std::ostringstream result;

  result << subtractionInstruction.mnemonic() << " (" << registerString(pointerRegister, false, false) << ")";

  return result.str();
}
