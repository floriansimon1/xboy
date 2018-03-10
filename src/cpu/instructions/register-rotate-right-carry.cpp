#include <sstream>

#include "../../debug/register-string.hpp"
#include "register-rotate-right-carry.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

RegisterRotateRightCarry::RegisterRotateRightCarry(CpuRegisterPointer cpuRegister, bool low):
  ConstantTimeInstruction(8, 0, 2),
  cpuRegister(cpuRegister),
  low(low)
{
}

void RegisterRotateRightCarry::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

  const bool rightBitSet = getBit(value, 0);

  gameboy.cpu.setCarryFlag(rightBitSet);
  gameboy.cpu.setHalfCarryFlag(false);
  gameboy.cpu.setSubtractFlag(false);
  gameboy.cpu.setZeroFlag(false);

  gameboy.cpu.setSingleByteRegister(cpuRegister, low, (
    (value >> 1) | (rightBitSet ? highBitInByte : 0)
  ));
}

std::string RegisterRotateRightCarry::toString() const {
  std::ostringstream result;

  result << "RRC " << registerString(cpuRegister, true, low);

  return result.str();
}
