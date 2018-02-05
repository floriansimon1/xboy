#include <sstream>

#include "two-bytes-registers-addition.hpp"
#include "../../debug/register-string.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"

TwoBytesRegistersAddition::TwoBytesRegistersAddition(CpuRegisterPointer source, CpuRegisterPointer destination):
  Instruction(8, 0, 1),
  source(source),
  destination(destination)
{
}

void TwoBytesRegistersAddition::execute(Gameboy &gameboy, const uint8_t *) const {
  const uint32_t value = gameboy.cpu.twoBytesRegister(destination) + gameboy.cpu.twoBytesRegister(source);

  gameboy.cpu.setHalfCarryFlag(
    (
      (gameboy.cpu.twoBytesRegister(source) & lowHalfByteMask)
      + (gameboy.cpu.twoBytesRegister(destination) & lowHalfByteMask)
    ) >> 4
  );

  gameboy.cpu.setCarryFlag(value >> 16);
  gameboy.cpu.setSubtractFlag(false);

  gameboy.cpu.setTwoBytesRegister(destination, value);
}

std::string TwoBytesRegistersAddition::toString() const {
  std::ostringstream result;

  result << "ADD " << registerString(destination, false, false) << ", " << registerString(source, false, false);

  return result.str();
}
