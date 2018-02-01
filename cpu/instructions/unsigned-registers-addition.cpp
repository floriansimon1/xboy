#include <sstream>

#include "../../debug/register-string.hpp"
#include "unsigned-registers-addition.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

UnsignedRegistersAddition::UnsignedRegistersAddition(
  CpuRegisterPointer to, bool toLow, CpuRegisterPointer from, bool fromLow, bool carry
):
  Instruction(4, 0, 1),
  fromLow(fromLow),
  toLow(toLow),
  carry(carry),
  from(from),
  to(to)
{
}

const char* UnsignedRegistersAddition::mnemonic() const {
  return carry ? "ADC" : "ADD";
}

void UnsignedRegistersAddition::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setSubtractFlag(false);

  const auto fromValue  = gameboy.cpu.singleByteRegister(to, toLow);
  const auto carryValue = gameboy.cpu.getCarryFlag() && carry ? 1 : 0;
  const auto toValue    = gameboy.cpu.singleByteRegister(from, fromLow);

  const uint8_t result = fromValue + toValue + carryValue;

  gameboy.cpu.setSingleByteRegister(to, toLow, result);

  gameboy.cpu.setZeroFlag(!result);
  gameboy.cpu.setCarryFlag(result < fromValue && result < toValue);
  gameboy.cpu.setHalfCarryFlag((fromValue & lowHalfByteMask) + (toValue & lowHalfByteMask) > lowHalfByteMask);
}

std::string UnsignedRegistersAddition::toString() const {
  std::ostringstream result;

  result << mnemonic() << ' '
         << registerString(to, true, toLow) << ", "
         << registerString(from, true, fromLow);

  return result.str();
}
