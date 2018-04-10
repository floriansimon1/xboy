#include <sstream>

#include "../../../debug/register-string.hpp"
#include "dereference-or.hpp"
#include "../../gameboy.hpp"

DereferenceOr::DereferenceOr(CpuRegisterPointer pointerRegister, bool exclusive):
  ConstantTimeInstruction(8, 0, 1),
  pointerRegister(pointerRegister),
  orInstruction(exclusive)
{
}

void DereferenceOr::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.mmu.read(gameboy, gameboy.cpu.twoBytesRegister(pointerRegister));

  orInstruction.execute(gameboy, &value);
}

std::string DereferenceOr::toString() const {
  std::ostringstream result;

  result << orInstruction.mnemonic() << " ("
         << registerString(pointerRegister, false, false)
         << ')';

  return result.str();
}
