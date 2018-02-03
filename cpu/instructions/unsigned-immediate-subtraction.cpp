#include "unsigned-immediate-subtraction.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

UnsignedImmediateSubtraction::UnsignedImmediateSubtraction(bool carry):
  Instruction(8, 1, 1),
  carry(carry)
{
}

const char* UnsignedImmediateSubtraction::mnemonic() const {
  return carry ? "SBC A," : "SUB";
}

void UnsignedImmediateSubtraction::execute(Gameboy &gameboy, const uint8_t *data) const {
  gameboy.cpu.setSubtractFlag(true);

  const auto subtract   = *data;
  const auto carryValue = gameboy.cpu.getCarryFlag() && carry ? 1 : 0;
  const auto aValue     = gameboy.cpu.singleByteRegister(&Cpu::af, false);

  const uint8_t result = aValue - subtract - carryValue;

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, result);

  gameboy.cpu.setZeroFlag(!result);
  gameboy.cpu.setCarryFlag(static_cast<uint16_t>(subtract) + carryValue > aValue);
  gameboy.cpu.setHalfCarryFlag(((carryValue + subtract) & lowHalfByteMask) > (aValue & lowHalfByteMask));
}

std::string UnsignedImmediateSubtraction::toString() const {
  return "SUB d8";
}
