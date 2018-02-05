#include "unsigned-immediate-addition.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

UnsignedImmediateAddition::UnsignedImmediateAddition(bool carry):
  Instruction(8, 1, 1),
  carry(carry)
{
}

const char* UnsignedImmediateAddition::mnemonic() const {
  return carry ? "ADC A, " : "ADD A, ";
}

void UnsignedImmediateAddition::execute(Gameboy &gameboy, const uint8_t *data) const {
  gameboy.cpu.setSubtractFlag(false);

  const auto aValue     = gameboy.cpu.singleByteRegister(&Cpu::af, false);
  const auto carryValue = gameboy.cpu.getCarryFlag() && carry ? 1 : 0;
  const auto addValue   = *data;

  const uint8_t result = aValue + addValue + carryValue;

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, result);

  gameboy.cpu.setZeroFlag(!result);
  gameboy.cpu.setCarryFlag(result < aValue && result < addValue);

  gameboy.cpu.setHalfCarryFlag(
    (aValue & lowHalfByteMask)
    + ((addValue + carryValue) & lowHalfByteMask)
    > lowHalfByteMask
  );
}

std::string UnsignedImmediateAddition::toString() const {
  return "ADD A, d8";
}
