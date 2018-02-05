#include <sstream>

#include "../../debug/register-string.hpp"
#include "dereference-and.hpp"
#include "../../gameboy.hpp"

DereferenceAnd::DereferenceAnd(CpuRegisterPointer pointerRegister):
  Instruction(8, 0, 1),
  pointerRegister(pointerRegister)
{
}

void DereferenceAnd::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto dataPointer = gameboy.mmu.memory + gameboy.cpu.twoBytesRegister(pointerRegister);

  andInstruction.execute(gameboy, dataPointer);
}

std::string DereferenceAnd::toString() const {
  std::ostringstream result;

  result << "AND (" << registerString(pointerRegister, false, false) << ')';

  return result.str();
}
