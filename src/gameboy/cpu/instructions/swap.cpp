#include <sstream>

#include "../../../debug/register-string.hpp"
#include "../../gameboy.hpp"
#include "../../../bit.hpp"
#include "swap.hpp"

Swap::Swap(CpuRegisterPointer cpuRegister, bool low):
  ConstantTimeInstruction(8, 0, 2),
  cpuRegister(cpuRegister),
  low(low)
{
}

void Swap::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

  gameboy.cpu.clearAllFlags();

  gameboy.cpu.setCarryFlag(getBit(value, 0));
  gameboy.cpu.setHalfCarryFlag(false);
  gameboy.cpu.setSubtractFlag(false);
  gameboy.cpu.setZeroFlag(false);

  gameboy.cpu.setSingleByteRegister(cpuRegister, low, (
    ((value & lowHalfByteMask) << 4)
    | ((value & highHalfByteMask) >> 4)
  ));
}

std::string Swap::toString() const {
  std::ostringstream result;

  result << "SWAP " << registerString(cpuRegister, true, low);

  return result.str();
}
