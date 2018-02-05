#include <sstream>

#include "../../debug/register-string.hpp"
#include "dereference-or.hpp"
#include "../../gameboy.hpp"

DereferenceOr::DereferenceOr(CpuRegisterPointer pointerRegister, bool exclusive):
  Instruction(8, 0, 1),
  pointerRegister(pointerRegister),
  orInstruction(exclusive)
{
}

void DereferenceOr::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto dataPointer = gameboy.mmu.memory + gameboy.cpu.twoBytesRegister(pointerRegister);

  orInstruction.execute(gameboy, dataPointer);
}

std::string DereferenceOr::toString() const {
  std::ostringstream result;

  result << orInstruction.mnemonic() << " ("
         << registerString(pointerRegister, false, false)
         << ')';

  return result.str();
}