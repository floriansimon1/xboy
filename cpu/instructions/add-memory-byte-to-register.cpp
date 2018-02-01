#include <sstream>

#include "../../debug/register-string.hpp"
#include "add-memory-byte-to-register.hpp"
#include "../../gameboy.hpp"

AddMemoryByteToRegister::AddMemoryByteToRegister(
  CpuRegisterPointer pointerRegister, bool carry
):
  Instruction(8, 0, 1),
  additionInstruction(pointerRegister, true, carry),
  pointerRegister(pointerRegister),
  carry(carry)
{
}

void AddMemoryByteToRegister::execute(Gameboy &gameboy, const uint8_t *data) const {
  const auto cheatRegisterValue = gameboy.cpu.singleByteRegister(pointerRegister, additionInstruction.low);
  const auto memoryValue        = gameboy.mmu.memory[gameboy.cpu.twoBytesRegister(pointerRegister)];

  gameboy.cpu.setSingleByteRegister(pointerRegister, additionInstruction.low, memoryValue);

  additionInstruction.execute(gameboy, data);

  gameboy.cpu.setSingleByteRegister(pointerRegister, additionInstruction.low, cheatRegisterValue);
}

std::string AddMemoryByteToRegister::toString() const {
  std::ostringstream result;

  result << additionInstruction.mnemonic() << " A, ("
         << registerString(pointerRegister, false, false) << ')';

  return result.str();
}
