#include <sstream>

#include "../../debug/register-string.hpp"
#include "single-byte-increment.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

SingleByteIncrement::SingleByteIncrement(CpuRegisterPointer cpuRegister, bool low, short sign):
  ConstantTimeInstruction(8, 0, 1),
  cpuRegister(cpuRegister),
  sign(sign),
  low(low)
{
}

void SingleByteIncrement::execute(Gameboy &gameboy, const uint8_t*) const {
  const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

  const auto result = value + sign;

  gameboy.cpu.setZeroFlag(!result);
  gameboy.cpu.setSubtractFlag(sign == -1);

  gameboy.cpu.setHalfCarryFlag(
    sign == -1
    ? !(value & lowHalfByteMask)
    : (value & lowHalfByteMask) == lowHalfByteMask
  );

  gameboy.cpu.setSingleByteRegister(cpuRegister, low, result);
}

std::string SingleByteIncrement::toString() const {
  std::ostringstream result;

  const auto mnemonic = sign == 1 ? "INC " : "DEC ";

  result << mnemonic << registerString(cpuRegister, true, low);

  return result.str();
}
