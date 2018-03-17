#include "signed-immediate-addition.hpp"
#include "../../gameboy.hpp"
#include "../../../bit.hpp"

SignedImmediateAddition::SignedImmediateAddition(): ConstantTimeInstruction(16, 1, 1)
{
}

void SignedImmediateAddition::execute(Gameboy &gameboy, const uint8_t *data) const {
  gameboy.cpu.setSubtractFlag(false);
  gameboy.cpu.setZeroFlag(false);

  const int8_t addValue = *reinterpret_cast<const int8_t*>(data);
  const auto oldValue   = gameboy.cpu.sp;

  const uint32_t result = oldValue + addValue;

  gameboy.cpu.sp = result;

  gameboy.cpu.setCarryFlag(result > maxUint16);

  gameboy.cpu.setHalfCarryFlag(
    (oldValue & lowHalfByteMask)
    + (addValue & lowHalfByteMask)
    > lowHalfByteMask
  );
}

std::string SignedImmediateAddition::toString() const {
  return "ADD SP, r8";
}
