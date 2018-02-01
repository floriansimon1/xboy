#include <sstream>

#include "subtract-memory-byte-to-register.hpp"
#include "../../debug/register-string.hpp"
#include "../../gameboy.hpp"

SubtractMemoryByteToRegister::SubtractMemoryByteToRegister(CpuRegisterPointer pointerRegister, bool carry):
  Instruction(8, 0, 1),
  subtractionInstruction(&Cpu::bc, true, carry),
  pointerRegister(pointerRegister),
  carry(carry)
{
}

void SubtractMemoryByteToRegister::execute(Gameboy &gameboy, const uint8_t *data) const {
  const auto cheatRegisterValue = gameboy.cpu.singleByteRegister(
    subtractionInstruction.cpuRegister,
    subtractionInstruction.low
  );

  const auto memoryValue = gameboy.mmu.memory[gameboy.cpu.twoBytesRegister(pointerRegister)];

  gameboy.cpu.setSingleByteRegister(
    subtractionInstruction.cpuRegister,
    subtractionInstruction.low,
    memoryValue
  );

  subtractionInstruction.execute(gameboy, data);

  gameboy.cpu.setSingleByteRegister(
    subtractionInstruction.cpuRegister,
    subtractionInstruction.low,
    cheatRegisterValue
  );
}

std::string SubtractMemoryByteToRegister::toString() const {
  std::ostringstream result;

  result << subtractionInstruction.mnemonic() << " (" << registerString(pointerRegister, false, false) << ")";

  return result.str();
}
