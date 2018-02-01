#include <sstream>

#include "unsigned-registers-subtraction.hpp"
#include "../../debug/register-string.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

UnsignedRegistersSubtraction::UnsignedRegistersSubtraction(
  CpuRegisterPointer cpuRegister,
  bool carry,
  bool low
):
  Instruction(4, 0, 1),
  cpuRegister(cpuRegister),
  carry(carry),
  low(low)
{
}

const char* UnsignedRegistersSubtraction::mnemonic() const {
  return carry ? "SBC A," : "SUB";
}

void UnsignedRegistersSubtraction::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.setSubtractFlag(true);

  const auto carryValue = gameboy.cpu.getCarryFlag() && carry ? 1 : 0;
  const auto toValue    = gameboy.cpu.singleByteRegister(&Cpu::af, false);
  const auto fromValue  = gameboy.cpu.singleByteRegister(cpuRegister, low);

  const uint8_t result = toValue - fromValue - carryValue;

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, result);

  gameboy.cpu.setZeroFlag(!result);
  gameboy.cpu.setCarryFlag(static_cast<uint16_t>(fromValue) + carryValue > toValue);
  gameboy.cpu.setHalfCarryFlag((fromValue & lowHalfByteMask) > (toValue & lowHalfByteMask));
}

std::string UnsignedRegistersSubtraction::toString() const {
  std::ostringstream result;

  result << mnemonic() << ' ' << registerString(cpuRegister, true, low);

  return result.str();
}
