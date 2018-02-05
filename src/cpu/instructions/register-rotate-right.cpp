#include <sstream>

#include "../../debug/register-string.hpp"
#include "register-rotate-right.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

RegisterRotateRight::RegisterRotateRight(CpuRegisterPointer cpuRegister, bool low):
  Instruction(8, 1, 1),
  cpuRegister(cpuRegister),
  low(low)
{
}

void RegisterRotateRight::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

  gameboy.cpu.setCarryFlag(getBit(value, 0));
  gameboy.cpu.setHalfCarryFlag(false);
  gameboy.cpu.setSubtractFlag(false);
  gameboy.cpu.setZeroFlag(false);

  gameboy.cpu.setSingleByteRegister(cpuRegister, low, value >> 1);
}

std::string RegisterRotateRight::toString() const {
  std::ostringstream result;

  result << "RR " << registerString(cpuRegister, true, low);

  return result.str();
}
