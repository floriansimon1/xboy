#include <sstream>

#include "../../debug/register-string.hpp"
#include "dereference-compare.hpp"
#include "../../gameboy.hpp"

DereferenceCompare::DereferenceCompare(CpuRegisterPointer pointerRegister):
  ConstantTimeInstruction(8, 0, 1),
  pointerRegister(pointerRegister),
  compareInstruction()
{
}

void DereferenceCompare::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.mmu.memory[gameboy.cpu.twoBytesRegister(pointerRegister)];

  compareInstruction.execute(gameboy, &value);
}

std::string DereferenceCompare::toString() const {
  std::ostringstream result;

  result << "CP (" << registerString(pointerRegister, false, false) << ')';

  return result.str();
}
