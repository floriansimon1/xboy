#include <sstream>

#include "../../debug/register-string.hpp"
#include "../../gameboy.hpp"
#include "registers-or.hpp"

RegistersOr::RegistersOr(CpuRegisterPointer cpuRegister, bool low, bool exclusive):
  ConstantTimeInstruction(4, 0, 1),
  low(low),
  cpuRegister(cpuRegister),
  orInstruction(exclusive)
{
}

void RegistersOr::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

  orInstruction.execute(gameboy, &value);
}

std::string RegistersOr::toString() const {
  std::ostringstream result;

  result << orInstruction.mnemonic() << ' ' << registerString(cpuRegister, true, low);

  return result.str();
}
