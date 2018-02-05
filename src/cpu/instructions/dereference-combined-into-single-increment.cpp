#include <sstream>

#include "dereference-combined-into-single-increment.hpp"
#include "../../debug/register-string.hpp"
#include "../../gameboy.hpp"

DereferenceCombinedIntoSingleIncrement::DereferenceCombinedIntoSingleIncrement(
  CpuRegisterPointer pointerRegister,
  CpuRegisterPointer targetRegister,
  const short        sign,
  bool               low
):
  Instruction(8, 0, 1),
  dereferenceInstruction(pointerRegister, targetRegister, low),
  sign(sign)
{
}

void DereferenceCombinedIntoSingleIncrement::execute(Gameboy &gameboy, const uint8_t *data) const {
  dereferenceInstruction.execute(gameboy, data);

  gameboy.cpu.*(dereferenceInstruction.targetRegister) += sign;
}

std::string DereferenceCombinedIntoSingleIncrement::toString() const {
  std::ostringstream result;

  const auto signChar = sign == -1 ? '-' : '+';

  result << "LD " << registerString(dereferenceInstruction.targetRegister, true, dereferenceInstruction.low)
         << ", (" << registerString(dereferenceInstruction.pointerRegister, false, false) << signChar << ')';

  return result.str();
}
