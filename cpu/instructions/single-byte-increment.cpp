#include <sstream>

#include "../../debug/register-string.hpp"
#include "single-byte-increment.hpp"
#include "../../gameboy.hpp"

SingleByteIncrement::SingleByteIncrement(CpuRegisterPointer cpuRegister, bool low, short sign):
  Instruction(8, 0, 1),
  cpuRegister(cpuRegister),
  sign(sign),
  low(low)
{
}

void SingleByteIncrement::execute(Gameboy &gameboy, const uint8_t*) {
  const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

  const auto result = value + sign;

  gameboy.cpu.setZeroFlag(!result);
  gameboy.cpu.setSubtractFlag(sign === -1);
  gameboy.cpu.setHalfCarryFlag(sign == 1 && !result);

  gameboy.cpu.setSingleByteRegister(cpuRegister, low, result);
}

std::string SingleByteIncrement::toString() {
  std::ostringstream result;

  const auto mnemonic = sign == 1 ? "INC " : "DEC ";

  result << mnemonic << registerString(cpuRegister, true, low);

  return result.str();
}

