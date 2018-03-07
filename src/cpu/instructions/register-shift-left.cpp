#include <sstream>

#include "../../debug/register-string.hpp"
#include "register-shift-left.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

RegisterShiftLeft::RegisterShiftLeft(CpuRegisterPointer cpuRegister, bool low):
  ConstantTimeInstruction(8, 0, 2),
  cpuRegister(cpuRegister),
  low(low)
{
}

void RegisterShiftLeft::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

  const auto result = value << 1;

  gameboy.cpu.setHalfCarryFlag(getBit(value, 3));
  gameboy.cpu.setCarryFlag(getBit(value, 7));
  gameboy.cpu.setSubtractFlag(false);
  gameboy.cpu.setZeroFlag(!result);

  gameboy.cpu.setSingleByteRegister(cpuRegister, low, result);
}

std::string RegisterShiftLeft::toString() const {
  std::ostringstream result;

  result << "SRA " << registerString(cpuRegister, true, low);

  return result.str();
}
