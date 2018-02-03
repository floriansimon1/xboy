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
  additionInstruction(carry)
{
}

void UnsignedRegistersAddition::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setSubtractFlag(false);

  const auto carryValue = gameboy.cpu.getCarryFlag() && additionInstruction.carry ? 1 : 0;
  const auto fromValue  = gameboy.cpu.singleByteRegister(&Cpu::af, false);
  const auto toValue    = gameboy.cpu.singleByteRegister(from, low);

  const uint8_t result = fromValue + toValue + carryValue;

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, result);

  gameboy.cpu.setZeroFlag(!result);
  gameboy.cpu.setCarryFlag(result < fromValue && result < toValue);
  gameboy.cpu.setHalfCarryFlag((fromValue & lowHalfByteMask) + (toValue & lowHalfByteMask) > lowHalfByteMask);
}

std::string UnsignedRegistersAddition::toString() const {
  std::ostringstream result;

  result << additionInstruction.mnemonic() << registerString(from, true, low);

  return result.str();
}
