#include <sstream>

#include "../../debug/register-string.hpp"
#include "add-memory-byte-to-register.hpp"
#include "../../gameboy.hpp"

AddMemoryByteToRegister::AddMemoryByteToRegister(
  CpuRegisterPointer pointerRegister,
  CpuRegisterPointer targetRegister,
  bool low,
  bool carry
):
  Instruction(8, 0, 1),
  additionInstruction(targetRegister, low, targetRegister, !low, carry),
  pointerRegister(pointerRegister),
  targetRegister(targetRegister),
  carry(carry),
  low(low)
{
}

void AddMemoryByteToRegister::execute(Gameboy &gameboy, const uint8_t *data) const {
  const auto cheatRegisterValue = gameboy.cpu.singleByteRegister(targetRegister, !low);
  const auto memoryValue        = gameboy.mmu.memory[gameboy.cpu.twoBytesRegister(pointerRegister)];

  gameboy.cpu.setSingleByteRegister(targetRegister, !low, memoryValue);

  additionInstruction.execute(gameboy, data);

  gameboy.cpu.setSingleByteRegister(targetRegister, !low, cheatRegisterValue);
}

std::string AddMemoryByteToRegister::toString() const {
  std::ostringstream result;

  result << additionInstruction.mnemonic() << ' ' << registerString(targetRegister, true, low)
         << ", " << registerString(pointerRegister, false, false);

  return result.str();
}
