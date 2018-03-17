#include <sstream>

#include "../../../debug/register-string.hpp"
#include "register-rotate-left.hpp"
#include "../../gameboy.hpp"
#include "../../../bit.hpp"

RegisterRotateLeft::RegisterRotateLeft(CpuRegisterPointer cpuRegister, bool low):
  ConstantTimeInstruction(8, 1, 1),
  cpuRegister(cpuRegister),
  low(low)
{
}

void RegisterRotateLeft::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

  const uint8_t carry = gameboy.cpu.getCarryFlag();

  gameboy.cpu.setCarryFlag(getBit(value, 7));
  gameboy.cpu.setHalfCarryFlag(false);
  gameboy.cpu.setSubtractFlag(false);
  gameboy.cpu.setZeroFlag(false);

  gameboy.cpu.setSingleByteRegister(cpuRegister, low, (value << 1) | carry);
}

std::string RegisterRotateLeft::toString() const {
  std::ostringstream result;

  result << "RL " << registerString(cpuRegister, true, low);

  return result.str();
}
