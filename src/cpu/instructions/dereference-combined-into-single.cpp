#include <sstream>

#include "dereference-combined-into-single.hpp"
#include "../../debug/register-string.hpp"
#include "../../gameboy.hpp"

DereferenceCombinedIntoSingle::DereferenceCombinedIntoSingle(
  CpuRegisterPointer pointerRegister,
  CpuRegisterPointer targetRegister,
  bool               low
):
  ConstantTimeInstruction(8, 0, 1),
  pointerRegister(pointerRegister),
  targetRegister(targetRegister),
  low(low)
{
}

void DereferenceCombinedIntoSingle::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setSingleByteRegister(targetRegister, low, gameboy.mmu.memory[
    gameboy.cpu.twoBytesRegister(pointerRegister)
  ]);
}

std::string DereferenceCombinedIntoSingle::toString() const {
  std::ostringstream result;

  result << "LD " << registerString(targetRegister, true, low)
         << ", (" << registerString(pointerRegister, false, false) << ')';

  return result.str();
}
