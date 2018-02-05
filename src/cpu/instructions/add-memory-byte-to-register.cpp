#include <sstream>

#include "../../debug/register-string.hpp"
#include "add-memory-byte-to-register.hpp"
#include "../../gameboy.hpp"

AddMemoryByteToRegister::AddMemoryByteToRegister(
  CpuRegisterPointer pointerRegister, bool carry
):
  ConstantTimeInstruction(8, 0, 1),
  additionInstruction(carry),
  pointerRegister(pointerRegister)
{
}

void AddMemoryByteToRegister::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto dataPointer = gameboy.mmu.memory + gameboy.cpu.twoBytesRegister(pointerRegister);

  additionInstruction.execute(gameboy, dataPointer);
}

std::string AddMemoryByteToRegister::toString() const {
  std::ostringstream result;

  result << additionInstruction.mnemonic() << '('
         << registerString(pointerRegister, false, false) << ')';

  return result.str();
}
