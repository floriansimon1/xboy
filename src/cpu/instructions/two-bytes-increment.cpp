#include <sstream>

#include "../../debug/register-string.hpp"
#include "two-bytes-increment.hpp"
#include "../../gameboy.hpp"

TwoBytesIncrement::TwoBytesIncrement(CpuRegisterPointer cpuRegister, short sign):
  ConstantTimeInstruction(8, 0, 1),
  cpuRegister(cpuRegister),
  sign(sign)
{
}

void TwoBytesIncrement::execute(Gameboy &gameboy, const uint8_t *) const {
  gameboy.cpu.*cpuRegister += sign;
}

std::string TwoBytesIncrement::toString() const {
  std::ostringstream result;

  const auto mnemonic = sign == 1 ? "INC " : "DEC ";

  result << mnemonic << registerString(cpuRegister, false, false);

  return result.str();
}
