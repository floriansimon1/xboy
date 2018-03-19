#include <sstream>

#include "../../../debug/register-string.hpp"
#include "increment-dereference.hpp"
#include "../../gameboy.hpp"
#include "../../../bit.hpp"

IncrementDereference::IncrementDereference(CpuRegisterPointer pointerRegister, const short sign):
  ConstantTimeInstruction(12, 0, 1),
  pointerRegister(pointerRegister),
  sign(sign)
{
}

void IncrementDereference::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto registerValue = gameboy.cpu.twoBytesRegister(pointerRegister);

  const auto value = gameboy.mmu[registerValue];

  const auto result = value + 1;

  gameboy.mmu.write(registerValue, value + 1);

  gameboy.cpu.setHalfCarryFlag(!(result & lowHalfByteMask));
  gameboy.cpu.setZeroFlag(!result);
}

std::string IncrementDereference::toString() const {
  std::ostringstream result;

  const auto mnemonic = sign == 1 ? "INC (" : "DEC (";

  result << mnemonic << registerString(pointerRegister, false, false) << ")";

  return result.str();
}