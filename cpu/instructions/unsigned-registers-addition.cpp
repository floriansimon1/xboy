#include <sstream>

#include "../../debug/register-string.hpp"
#include "unsigned-registers-addition.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

UnsignedRegistersAddition::UnsignedRegistersAddition(
  CpuRegisterPointer from,
  bool low,
  bool carry
):
  Instruction(4, 0, 1),
  low(low),
  from(from),
  carry(carry)
{
}

const char* UnsignedRegistersAddition::mnemonic() const {
  return carry ? "ADC" : "ADD";
}

void UnsignedRegistersAddition::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setSubtractFlag(false);

  const auto fromValue  = gameboy.cpu.singleByteRegister(&Cpu::af, false);
  const auto carryValue = gameboy.cpu.getCarryFlag() && carry ? 1 : 0;
  const auto toValue    = gameboy.cpu.singleByteRegister(from, low);

  const uint8_t result = fromValue + toValue + carryValue;

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, result);

  gameboy.cpu.setZeroFlag(!result);
  gameboy.cpu.setCarryFlag(result < fromValue && result < toValue);
  gameboy.cpu.setHalfCarryFlag((fromValue & lowHalfByteMask) + (toValue & lowHalfByteMask) > lowHalfByteMask);
}

std::string UnsignedRegistersAddition::toString() const {
  std::ostringstream result;

  result << mnemonic() << " A, " << registerString(from, true, low);

  return result.str();
}
