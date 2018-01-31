#include <sstream>

#include "../../debug/register-string.hpp"
#include "unsigned-registers-addition.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

UnsignedRegistersAddition::UnsignedRegistersAddition(
  CpuRegisterPointer to, bool toLow, CpuRegisterPointer from, bool fromLow
):
  Instruction(4, 0, 1),
  fromLow(fromLow),
  toLow(toLow),
  from(from),
  to(to)
{
}

void UnsignedRegistersAddition::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setSubtractFlag(false);

  const auto fromValue = gameboy.cpu.singleByteRegister(to, toLow);
  const auto toValue   = gameboy.cpu.singleByteRegister(from, fromLow);

  const uint8_t result = fromValue + toValue;

  gameboy.cpu.setSingleByteRegister(to, toLow, result);

  gameboy.cpu.setZeroFlag(!result);
  gameboy.cpu.setCarryFlag(result < fromValue && result < toValue);
  gameboy.cpu.setHalfCarryFlag((fromValue & lowHalfByteMask) + (toValue & lowHalfByteMask) > lowHalfByteMask);
}

std::string UnsignedRegistersAddition::toString() const {
  std::ostringstream result;

  result << "ADD " << registerString(to, true, toLow) << ", " << registerString(from, true, fromLow);

  return result.str();
}
