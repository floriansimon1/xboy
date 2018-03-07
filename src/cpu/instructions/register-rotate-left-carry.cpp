#include <sstream>

#include "../../debug/register-string.hpp"
#include "register-rotate-left-carry.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

RegisterRotateLeftCarry::RegisterRotateLeftCarry(CpuRegisterPointer cpuRegister, bool low):
  ConstantTimeInstruction(8, 0, 2),
  cpuRegister(cpuRegister),
  low(low)
{
}

void RegisterRotateLeftCarry::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

  const bool leftBitSet = getBit(value, 7);

  gameboy.cpu.setCarryFlag(leftBitSet);
  gameboy.cpu.setHalfCarryFlag(false);
  gameboy.cpu.setSubtractFlag(false);
  gameboy.cpu.setZeroFlag(false);

  gameboy.cpu.setSingleByteRegister(cpuRegister, low, (
    (value << 1) | (leftBitSet ? 1 : 0)
  ));
}

std::string RegisterRotateLeftCarry::toString() const {
  std::ostringstream result;

  result << "RLC " << registerString(cpuRegister, true, low);

  return result.str();
}
