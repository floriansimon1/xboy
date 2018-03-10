#include <sstream>

#include "../../debug/register-string.hpp"
#include "register-shift-right.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

RegisterShiftRight::RegisterShiftRight(CpuRegisterPointer cpuRegister, bool low):
  ConstantTimeInstruction(8, 0, 2),
  cpuRegister(cpuRegister),
  low(low)
{
}

void RegisterShiftRight::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

  // http://z80-heaven.wikidot.com/instructions-set:sra
  const auto result = (value & highBitInByte) | value >> 1;

  gameboy.cpu.setCarryFlag(getBit(value, 0));
  gameboy.cpu.setHalfCarryFlag(false);
  gameboy.cpu.setSubtractFlag(false);
  gameboy.cpu.setZeroFlag(!result);

  gameboy.cpu.setSingleByteRegister(cpuRegister, low, result);
}

std::string RegisterShiftRight::toString() const {
  std::ostringstream result;

  result << "SRA " << registerString(cpuRegister, true, low);

  return result.str();
}
