#include <sstream>

#include "../../debug/register-string.hpp"
#include "two-bytes-increment.hpp"
#include "../../gameboy.hpp"

TwoBytesIncrement::TwoBytesIncrement(CpuRegisterPointer cpuRegister, short sign):
  Instruction(8, 0, 1),
  cpuRegister(cpuRegister),
  sign(sign)
{
}

void TwoBytesIncrement::execute(Gameboy &gameboy, const uint8_t*) {
  const auto value = gameboy.cpu.twoBytesRegister(cpuRegister);

  gameboy.cpu.*cpuRegister = value + sign;
}

std::string TwoBytesIncrement::toString() {
  std::ostringstream result;

  const auto mnemonic = sign == 1 ? "INC " : "DEC ";

  result << mnemonic << registerString(cpuRegister, false, false);

  return result.str();
}

