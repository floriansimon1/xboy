#include <sstream>

#include "../../../debug/register-string.hpp"
#include "registers-compare.hpp"
#include "../../gameboy.hpp"

RegistersCompare::RegistersCompare(CpuRegisterPointer cpuRegister, bool low):
  ConstantTimeInstruction(4, 0, 1),
  cpuRegister(cpuRegister),
  low(low),
  compareInstruction()
{
}

void RegistersCompare::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

  compareInstruction.execute(gameboy, &value);
}

std::string RegistersCompare::toString() const {
  std::ostringstream result;

  result << "CP " << registerString(cpuRegister, true, low);

  return result.str();
}
